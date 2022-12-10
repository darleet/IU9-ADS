;---1---

(define memoized-factorial
  (let ((memo-res '()))
    (lambda (n)
      (let* ((step-res (assoc n memo-res)))
        (if step-res
            (cadr step-res)
            (let ((new-res
                   (cond ((= n 0) 1)
                         (else (* n (memoized-factorial (- n 1)))))))
              (set! memo-res (cons (list n new-res) memo-res))
              new-res))))))

;---2---

(define-syntax lazy-cons
  (syntax-rules ()
    ((_ a b) `('lazy-cons ,(cons a (delay b))))))

(define (lazy-car p)
  (caadr p))

(define (lazy-cdr p)
  (force (cdadr p)))

(define (lazy-head xs k)
  (define (loop xs i)
    (if (= i k)
        '()
        (cons (lazy-car xs) (loop (lazy-cdr xs) (+ i 1)))))
  (loop xs 0))

(define (lazy-ref xs k)
  (define (loop xs i)
    (if (= i k)
        (lazy-car xs)
        (loop (lazy-cdr xs) (+ i 1))))
  (loop xs 1))
  
(define (naturals n)
  (lazy-cons n (naturals (+ n 1))))

(define (factorials n)
  (lazy-cons (fact-find n) (factorials (+ n 1))))

(define (fact-find n)
  (define (loop n res)
    (if (zero? n)
        res
        (loop (- n 1) (* res n))))
  (loop n 1))

(define (lazy-factorial n)
  (lazy-ref (factorials 0) (+ n 1)))

#|
(begin
  (display (lazy-head (naturals 10) 12)) (newline)
  (display (lazy-ref (naturals 10) 12)) (newline)
  (display (lazy-factorial 10)) (newline)
  (display (lazy-factorial 50)) (newline))
|#


;---3---

(define (read-words)
  (let loop ((symbol (read-char))
             (words '())
             (word '()))
    (cond ((and (eof-object? symbol) (not (null? word)))
           (append words (list (list->string word))))
          ((eof-object? symbol) words)
          ((not (or (equal? symbol #\newline)
                    (equal? symbol #\space)
                    (equal? symbol #\tab)))
           (loop (read-char) words (append word (list symbol))))
          ((not (null? word))
           (loop (read-char) (append words (list (list->string word))) '()))
          (else (loop (read-char) words '())))))


;---4---

(define-syntax define-struct
  (syntax-rules ()
    ((_ name fields ...)



