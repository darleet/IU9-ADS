;---1---

(define call/cc call-with-current-continuation)
(define exit #f)

(define (use-assertions)
  (call/cc (lambda (c) (set! exit c))))

(define-syntax assert
  (syntax-rules ()
    ((_ expr)
     (if expr
         (begin
           (display "FAILED: ")
           (display (quote expr))
           (exit))))))

(use-assertions)

(define (1/x x)
  (assert (zero? x))
  (write (/ 1 x))
  (newline))

(map 1/x '(1 2 3 4 5))
(map 1/x '(-2 -1 0 1 2))


;---2---

(define (save-data var path)
  (call-with-output-file path
    (lambda (port)
      (write var port)
      (newline port))))

(define (load-data path)
  (call-with-input-file path
    (lambda (port)
      (write (read port))
      (newline))))
      
(define (line-count path)
  (call-with-input-file path
    (lambda (port)
      (define (loop 
      
