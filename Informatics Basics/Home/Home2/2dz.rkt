       

;---3---

(define (whitespace? char)
  (or
   (equal? char #\space)
   (equal? char #\newline)
   (equal? char #\return)
   (equal? char #\tab)))
      
; Алгоритмическая сложность - O(n), n - длина строки
(define (string-trim-left str)
  (let ((xs (string->list str)))
    (define (loop xs)
      (cond ((null? xs) '()) ; если вдруг нам передали пустой список
            ((whitespace? (car xs)) (loop (cdr xs)))
            (else xs)))
    (list->string (loop xs))))

; Алгоритмическая сложность - O(n^2) из-за процедуры append
(define (string-trim-right str)
  (let ((xs (string->list str)))
    (define (loop xs ws-buffer) ; создали буфер для пробельных символов
      (cond ((null? xs) '())
            ((whitespace? (car xs))
             (loop (cdr xs) (append ws-buffer (list (car xs)))))
            ((not (null? ws-buffer))
             (append ws-buffer (cons (car xs) (loop (cdr xs) '()))))
            (else
             (cons (car xs) (loop (cdr xs) '())))))
    (list->string (loop xs '()))))

; Алгоритмическая сложность - O(n^2)
(define (string-trim str)
  (string-trim-right (string-trim-left str)))

; для ачивки по list-trim-right аналогично:

(define (list-trim-right xs)
    (define (loop xs ws-buffer) ; создали буфер для пробельных символов
      (cond ((null? xs) '())
            ((whitespace? (car xs))
             (loop (cdr xs) (append ws-buffer (list (car xs)))))
            ((not (null? ws-buffer))
             (append ws-buffer (cons (car xs) (loop (cdr xs) '()))))
            (else
             (cons (car xs) (loop (cdr xs) '())))))
    (loop xs '()))

; Алгоритмическая сложность - O(n), n - длина a+b
(define (string-prefix? a b)
  (let ((la (string->list a))
        (lb (string->list b)))
    (define (loop la lb status)
      (cond ((or (null? la) (not status)) status) ; конец первой строки
            ((null? lb) (not status)) ; конец второй строки
            (else (loop (cdr la) (cdr lb) (equal? (car la) (car lb))))))
    (loop la lb #t)))

; Алгоритмическая сложность - O(n), n - длина a
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

; Алгоритмическая сложность - O(n), n - длина b
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

; Алгоритмическая сложность - O(n^2) из-за процедуры append
(define (string-split str sep)
  (let ((lstr (string->list str))
        (lsep-init (string->list sep)))
    (define (loop buff-lsep lstr lsep res)
      (cond ((null? lstr)
             (append res buff-lsep))
            ((null? lsep)
             (loop '()
                   (cdr lstr)
                   lsep-init
                   (append res (string-list (car lstr)))))
            ((equal? (car lstr) (car lsep))
             (loop (append buff-lsep (string-list (car lsep)))
                   (cdr lstr)
                   (cdr lsep)
                   res))
            (else
             (loop '()
                   (cdr lstr)
                   lsep-init
                   (append res buff-lsep (string-list (car lstr)))))))
    (loop '() lstr lsep-init '())))


;---4---

(define (size-count linear-size sizes)
  (if (not (null? sizes))
      (size-count (* linear-size (car sizes)) (cdr sizes))
      linear-size))

(define (make-multi-vector sizes . fill)
  (if (null? fill)
      (list 'multi-vector sizes (make-vector (size-count 1 sizes)))
      (list 'multi-vector sizes (make-vector (size-count 1 sizes) (car fill)))))

(define (multi-vector? m)
  (and (not (vector? m)) (list? m) (equal? (car m) 'multi-vector)))

; Реализуем многомерность при помощи линейного расположения элементов

(define (find-index m indices)
  (let ((indices-rev (reverse indices))
        (sizes-rev (reverse (cadr m))))
    (define (loop pointer dim-linear-size indices-rev sizes-rev)
      (if (not (null? indices-rev))
          (loop (+ pointer (* (car indices-rev) (car sizes-rev))) ; Указатель
                (* dim-linear-size (car sizes-rev)) ; Линейный размер на итерации
                (cdr indices-rev)
                (cdr sizes-rev))
          pointer))
    (loop (car indices-rev) 1 (cdr indices-rev) sizes-rev)))
; сразу указали на индекс в последнем размере вектора

(define (multi-vector-set! m indices element)
  (vector-set! (caddr m) (find-index m indices) element))

(define (multi-vector-ref m indices)
  (vector-ref (caddr m) (find-index m indices)))

;---5---

(define (o . procs)
  (define (loop procs)
    (if (null? procs)
        (lambda (x) x)
        (let ((proc (car procs)))
          (if (null? (cdr procs))
              proc
              (lambda (x) (proc ((loop (cdr procs)) x)))))))
  (loop procs))

(define (f x) (+ x 2))
(define (g x) (* x 3))
(define (h x) (- x))

