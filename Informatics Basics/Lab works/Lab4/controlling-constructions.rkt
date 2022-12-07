(define-syntax when
  (syntax-rules ()
    ((_ cond? body ...)
     (if cond? (begin body ...)))))

(define-syntax unless
  (syntax-rules ()
    ((_ cond? body ...)
     (if (not cond?) (begin body ...)))))

(define x 1)
(when (> x 0) (display "x > 0") (newline))
(unless (= x 0) (display "x != 0") (newline))


(define-syntax for
  (syntax-rules (in as)
    ((_ i in xs body ...)
     (let loop ((vals xs))
       (if (not (null? vals))
           (let ((i (car vals)))
             body ...
             (loop (cdr vals))))))
    ((_ xs as i body ...)
     (for i in xs body ...))))

(newline)
(for i in '(1 2 3)
  (for j in '(4 5 6)
    (display (list i j))
    (newline)))

(newline)
(for '(1 2 3) as i
  (for '(4 5 6) as j
    (display (list i j))
    (newline)))

(define-syntax while
  (syntax-rules ()
    ((while cond? body ...)
     (let loop ()
       (if cond? (begin body ... (loop)))))))

(define-syntax repeat
  (syntax-rules (until)
    ((repeat (body ...) until cond?)
     (let loop ()
       body ...
       (if (not cond?) (loop))))))

(newline)
(let ((i 0)
      (j 0))
  (repeat ((set! j 0)
           (repeat ((display (list i j))
                    (set! j (+ j 1)))
                   until (= j 3))
           (set! i (+ i 1))
           (newline))
          until (= i 3)))

(define-syntax cout
  (syntax-rules (<< endl)
    ((_ << endl)
     (newline))
    ((_ << endl . expr)
     (begin (newline)
            (cout . expr)))
    ((_ << expr1)
     (display expr1))
    ((_ << expr1 . expr)
     (begin (display expr1)
            (cout . expr)))))

(cout << "a = " << 1 << endl << "b = " << 2 << endl)