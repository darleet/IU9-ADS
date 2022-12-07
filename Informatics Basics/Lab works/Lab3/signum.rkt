(load "trace.rkt")
(load "unit-test.rkt")

(define (signum x)
  (cond
    ((< x 0) -1)
    ((= x 0)  1)
    (else     1)))

(define the-tests
  (list (test (signum -2) -1)
        (test (signum  0)  0)
        (test (signum  2)  1)))

(define next-tests
  (list (test (next) 6)
        (test (next) 8)
        (test (next) 8)))

(next)
(next)
(next)
(next)
(next)

(run-tests the-tests)
(run-tests next-tests)