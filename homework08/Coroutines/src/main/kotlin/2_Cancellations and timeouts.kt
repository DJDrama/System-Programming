import kotlinx.coroutines.*

fun printSeparator() {
    println("====================================================================")
}

fun main() = runBlocking {
    cancelExample()

    cancellationCooperativeExample()
    printSeparator()
    cancellableCooperativeExample()
    printSeparator()
    closeResourceWithFinally()
    printSeparator()
    nonCancellableBlock()
    printSeparator()
    //timeOut()
    printSeparator()
    timeOutWithoutException()
}

suspend fun cancelExample() = coroutineScope {
    val job = launch {
        repeat(1000) { i ->
            println("Job: I'm sleeping $i ...")
            delay(500L)
        }
    }
    delay(1300L)
    println("Main: I'm tired of waiting!")
    job.cancel() // cancels the job
    job.join() // waits for job's completion
    println("Main: Now I can quit!");
}
// (results)
// Job: I'm sleeping 0 ...
// Job: I'm sleeping 1 ...
// Job: I'm sleeping 2 ...
// Main: I'm tired of waiting!
// Main: Now I can quit!

/* Coroutine cancellation is cooperative */
// If a coroutine is working in a computation and does not check for cancellation,
// then it cannot be cancelled.
suspend fun cancellationCooperativeExample() = coroutineScope {
    val startTime = System.currentTimeMillis()
    val job = launch(Dispatchers.Default) {
        var nextPrintTime = startTime
        var i = 0
        while (i < 5) {
            if (System.currentTimeMillis() >= nextPrintTime) {
                println("Job: I'm sleeping ${i++} ...")
                nextPrintTime += 500L
            }
        }
    }
    delay(1300L)
    println("I'm tired of waiting!")
    job.cancelAndJoin()
    println("Now i can quit!")
}

/* Make computation cancellable */
// Two ways for cancellation: yield or check cancellation status
suspend fun cancellableCooperativeExample() = coroutineScope {
    val startTime = System.currentTimeMillis()
    val job = launch(Dispatchers.Default) {
        var nextPrintTime = startTime
        var i = 0
        while (isActive) {
            // yield()
            if (System.currentTimeMillis() >= nextPrintTime) {
                println("Job: I'm sleeping ${i++} ...")
                nextPrintTime += 500L
            }
        }
    }
    delay(1300L)
    println("I'm tired of waiting!")
    job.cancelAndJoin()
    println("Now i can quit!")
}

/* Closing resources with finally */
// Both join() and cancelAndJoin() wait for all finalization actions to complete.
suspend fun closeResourceWithFinally() = coroutineScope {
    val job = launch {
        try {
            repeat(1000) { i ->
                println("Job: I'm sleeping $i ...")
                delay(500L)
            }
        } finally {
            println("Job: I'm running finally")
        }
    }
    delay(1300L)
    println("I'm tired of waiting!")
    job.cancelAndJoin()
    println("Now i can quit!")
}

/* Run non-cancellable block */
suspend fun nonCancellableBlock() = coroutineScope {
    val job = launch {
        try {
            repeat(1000) { i ->
                println("Job: I'm sleeping $i ...")
                delay(500L)
            }
        } finally {
            withContext(NonCancellable) {
                println("Job: I'm running finally!")
                delay(1000L) // without NonCancellable, this line won't execute when cancellation
                println("Job: I've just delayed for 1 sec because I'm non-cancellable!")
            }
        }
    }
    delay(1300L)
    println("I'm tired of waiting!")
    job.cancelAndJoin()
    println("Now i can quit!")
}

/* Timeout */
// Exception in thread "main" kotlinx.coroutines.TimeoutCancellationException: Timed out waiting for 1300 ms
// Inside a cancelled coroutine, CancellationException is considered to be a normal reason for coroutine completion.
suspend fun timeOut() = coroutineScope {
    withTimeout(1300L) {
        repeat(1000) { i ->
            println("I'm sleeping $i ...")
            delay(500L)
        }
    }
}

suspend fun timeOutWithoutException() = coroutineScope {
    val result = withTimeoutOrNull(1300L) {
        repeat(1000) { i ->
            println("I'm sleeping $i ...")
            delay(500L)
        }
        "Done" // will get cancelled before it produces this result
    }
    println("Result is $result")
}