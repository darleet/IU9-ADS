;---1---

(define (my-range a b d)
  (define (loop a xs)
    (if (< (+ a d) b)
        (loop (+ a d) (append xs (list a)))
        (append xs (list a))))
  (loop a '()))

(define (my-flatten xs)
  (define (loop elem-end xs-end)
    (write elem-end) (display " - ") (write xs-end) (newline)
    (if (not (null? xs-end)) ; Если остались элементы в главном списке
        (cond ((and (not (null? elem-end)) (pair? (car xs-end))) ; вл. список списков
               (loop elem-end (car xs-end))) ; войдем внутрь вл. списка во вл. списке
              ((and (not (null? elem-end)) (not (null? (cdr xs-end)))) ; вл. список
               (cons (car xs-end) (loop elem-end (cdr xs-end)))) ; проход по списку
              ((pair? (car xs-end)) ; Если сл. элемент - список (пара)
               (loop (cdr xs-end) (car xs-end)))
              ((not (null? elem-end)) ; Пара вл. эл. и оставшихся в главном списке
               (cons (car xs-end) (loop '() elem-end)))
              (else (cons (car xs-end) (loop '() (cdr xs-end))))) ; Обычный случайы
        '()))
  (loop '() xs))
