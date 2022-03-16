- Open, read
  # 약 0.0005000 seconds

- fgetc, fputc
  # 약 0.0030000 seconds

- fgets, fputs
  # 약 0.0045000 seconds

- fread, fwrite
  # 약 0.0039000 seconds

- Mmap
  # 약 0.0023000 seconds

- Scattered, gathered(Vector)
  # 약 0.0030000 seconds


(순위 - Fastest) 
(Open, read) > Mmap > (Scattered, gathered(Vector)), (fgetc, fputc) > (fread, fwrite) > (fgets, fputs)
