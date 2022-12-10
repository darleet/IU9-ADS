(define (my-range a b d)
  (define (loop a xs)
    (if (< (+ a d) b)
        (loop (+ a d) (append xs (list a)))
        (append xs (list a))))
  (loop a '()))

(define (my-flatten xs)
  (define (loop elem-end xs-end)
    (write elem-end) (display " - ") (write xs-end) (newline)
    (if (not (null? xs-end)) ; если остались элементы в главном списке
        (cond ((and (not (null? elem-end)) (pair? (car xs-end))) 
               (loop elem-end (car xs-end))) ; войдем внутрь вл. списка во вл.списке
              ((and (not (null? elem-end)) (not (null? (cdr xs-end)))) 
               (cons (car xs-end) (loop elem-end (cdr xs-end)))) 
              ((pair? (car xs-end)) ; если сл. элемент - список (пара)
               (loop (cdr xs-end) (car xs-end)))
              ((not (null? elem-end)) ; пара вл. эл. и оставшихся в главном списке
               (cons (car xs-end) (loop '() elem-end)))
              (else
               (cons (car xs-end) (loop '() (cdr xs-end))))) ; обычный случай
        '()))
  (loop '() xs))

(define (my-element? x xs)
  (define (loop status xs)
    (if (not (null? xs))
        (loop (or (equal? (car xs) x) status) (cdr xs))
        status))
  (loop #f xs))

(define (my-filter pred? xs)
  (define (loop xs-filtered xs)
    (cond ((null? xs) xs-filtered)
          ((pred? (car xs)) (loop (append xs-filtered (list (car xs))) (cdr xs)))
          (else (loop xs-filtered (cdr xs)))))
  (loop '() xs))

(define (my-fold-left op xs)
  (define (loop result xs)
    (if (null? xs)
        result
        (loop (op result (car xs)) (cdr xs))))
  (loop (car xs) (cdr xs)))

(define (my-fold-right op xs)
  (define (loop xs)
    (if (null? (cdr xs))
        (car xs)
        (op (car xs) (loop (cdr xs)))))
  (loop xs))