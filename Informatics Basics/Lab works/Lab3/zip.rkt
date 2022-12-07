(load "trace.rkt")
(load "unit-test.rkt")

(define counter 0)
(define (next)
  (set! counter
        (+ counter 1))
  counter)

(define (zip . xss)
  (if (or (null? xss)
          (null? (trace-ex (car xss))))
      '()
      (cons (map car xss)
            (apply zip (map cdr (trace-ex xss))))))