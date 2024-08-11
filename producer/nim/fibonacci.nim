import bigints

proc fib() =
  let filename = "fibonacci.txt"
  var file: File
  try:
    file = open(filename, fmWrite)
  except IOError:
    stderr.writeLine("Error opening file '" & filename & "'")
    quit(1)
  defer:
    file.close()

  const CHUNK_SIZE = 10_000
  var a: BigInt = 0.initBigInt
  var b: BigInt = 1.initBigInt
  var n: int = 0
  while true:
    for i in 0 ..< CHUNK_SIZE:
      file.writeLine(a)
      let c = a + b
      a = b
      b = c
    file.flushFile()
    n += CHUNK_SIZE
    echo n, " total numbers written."

fib()
