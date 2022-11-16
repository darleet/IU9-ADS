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


;---2---

(define (member? x xs) 
  (define (loop status xs)
    (if (or (null? xs) status)
        status
        (loop (equal? (car xs) x) (cdr xs))))
  (loop #f xs))

(define (list->set xs)
  (define (loop set xs)
    (cond ((null? xs) set)
          ((not (member? (car xs) set)) (loop (cons (car xs) set) (cdr xs)))
          (else (loop set (cdr xs)))))
  (loop '() xs))
        
(define (set? xs)
  (define (loop status xs-head xs-tail)
    (if (or (null? xs-tail) status)
        (not status)
        (loop
         (member? (car xs-tail) xs-head)
         (append xs-head (list (car xs-tail)))
         (cdr xs-tail))))
  (loop #f '() xs))
        
(define (union xs ys)
  (define (loop set xs ys)
    (cond ((and (null? xs) (null? ys)) ; если закончились множества для перебора
           set)
          ((member? (car ys) set) ; если элемент из ys уже был
           (loop set xs (cdr ys)))
          ((null? xs) ; если закончились xs
           (loop (cons (car ys) set) xs (cdr ys)))
          ((member? (car xs) set) ; если вдруг xs не мн-во, сделаем его мн-вом :)
           (loop set (cdr xs) ys))
          (else ; иначе просто пройдём по xs 
           (loop (cons (car xs) set) (cdr xs) ys))))
  (loop '() xs ys))

(define (intersection xs ys)
  (define (loop set xs)
    (cond ((null? xs) set)
          ((member? (car xs) ys) (loop (append set (list (car xs))) (cdr xs)))
          (else (loop set (cdr xs)))))
  (loop '() xs))

(define (difference xs ys)
  (define (loop set xs)
    (cond ((null? xs)
           set)
          ((not (member? (car xs) ys))
           (loop (append set (list (car xs))) (cdr xs)))
          (else
           (loop set (cdr xs)))))
  (loop '() xs))

(define (symmetric-difference xs ys)
  (define (loop set xs-tail ys-tail)
    (cond ((and (null? xs-tail) (null? ys-tail))
           set)
          ((and (null? xs-tail) (not (member? (car ys-tail) xs)))
           (loop (cons (car ys-tail) set) xs-tail (cdr ys-tail)))
          ((null? xs-tail)
           (loop set xs-tail (cdr ys-tail)))
          ((not (member? (car xs-tail) ys))
           (loop (cons (car xs-tail) set) (cdr xs-tail) ys-tail))
          (else
           (loop set (cdr xs-tail) ys-tail))))
  (loop '() xs ys))
           
(define (set-eq? xs ys)
  (define (loop status xs)
    (if (or (null? xs) (not status))
        status
        (loop (member? (car xs) ys) (cdr xs)))) 
  (and (equal? (length xs) (length ys)) (loop #t xs)))
        

;---3---

(define (whitespace? char)
  (or
   (equal? char #\space)
   (equal? char #\newline)
   (equal? char #\return)
   (equal? char #\tab)))
      

(define (string-trim-left str)
  (let ((str-list (string->list str)))
    (define (loop str-list)
      (cond ((null? str-list) '()) ; если вдруг нам передали пустой список
            ((whitespace? (car str-list)) (loop (cdr str-list)))
            (else str-list)))
    (list->string (loop str-list))))

(define (string-trim-right str)
  (let ((sl-tail (string->list str)))
    (define (loop sl-head sl-tail ws-buffer) ; создали буфер для пробельных символов
      (cond ((null? sl-tail) ; если строка закончилась
             sl-head)
            ((whitespace? (car sl-tail)) ; встретили пробельный символ
             (loop sl-head (cdr sl-tail) (append ws-buffer (list (car sl-tail)))))
            (else ; иначе, если мы встречаем просто символ
             (loop
              (append sl-head ws-buffer (list (car sl-tail)))
              (cdr sl-tail)
              '()))))
    (list->string (loop '() sl-tail '()))))


; для ачивки по list-trim-right аналогично:

(define (list-trim-right lst)
  (let ((l-tail lst))
    (define (loop l-head l-tail ws-buffer) ; создали буфер для пробельных символов
      (cond ((null? l-tail) ; если строка закончилась
             l-head)
            ((whitespace? (car l-tail)) ; встретили пробельный символ
             (loop l-head (cdr l-tail) (append ws-buffer (list (car l-tail)))))
            (else ; иначе, если мы встречаем просто символ
             (loop
              (append l-head ws-buffer (list (car l-tail)))
              (cdr l-tail)
              '()))))
    (loop '() l-tail '())))


(define (string-prefix? a b)
  (let ((la (string->list a))
        (lb (string->list b)))
    (define (loop la lb status)
      (cond ((or (null? la) (not status)) status) ; конец первой строки
            ((null? lb) (not status)) ; конец второй строки
            (else (loop (cdr la) (cdr lb) (equal? (car la) (car lb))))))
    (loop la lb #t)))


(define (string-suffix? a b)
  (let ((la (string->list a))
        (lb (string->list b)))
    (define (loop buff-la lb)
      (cond ((null? lb) ; закончились обе строки? (если да => первая в конце второй)
             (null? buff-la))
            ((or (null? buff-la) (not (equal? (car buff-la) (car lb))))
             (loop la (cdr lb))) ; если элементы не равны или буфер закончился
            (else
             (loop (cdr buff-la) (cdr lb)))))
    (loop la lb)))


(define (string-infix? a b)
  (let ((la (string->list a))
        (lb (string->list b)))
    (define (loop buff-la lb)
      (cond ((or (null? buff-la) (null? lb))
             (null? buff-la))
            ((equal? (car buff-la) (car lb))
             (loop (cdr buff-la) (cdr lb)))
            (else
             (loop la (cdr lb)))))
    (loop la lb)))

(define (string-list char)
  (list (list->string (list char))))

(define (string-split str sep)
  (let ((lstr (string->list str))
        (lsep-init (string->list sep)))
    (define (loop buff-lsep lstr lsep res)
      (cond ((null? lstr)
             (append res buff-lsep))
            ((null? lsep)
             (loop '() (cdr lstr) lsep-init (append res (string-list (car lstr)))))
            ((equal? (car lstr) (car lsep))
             (loop
              (append buff-lsep (string-list (car lsep)))
              (cdr lstr)
              (cdr lsep)
              res))
            (else
             (loop
              '()
              (cdr lstr)
              lsep-init
              (append res buff-lsep (string-list (car lstr)))))))
    (loop '() lstr lsep-init '())))