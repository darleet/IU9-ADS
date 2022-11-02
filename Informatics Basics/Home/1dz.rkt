(define (day-of-week day month year)
  (let* ((a (quotient (- 14 month) 12))
         (y (- year a))
         (m (- (+ (* 12 a) month) 2))
         (// (lambda (a b) (quotient a b))))
    (remainder
     (+ day
        y
        (// y 4)
        (- (// y 100))
        (// y 400)
        (// (* 31 m) 12)
        7000)
     7)))

(define (quad-solve a b c)
  (let ((d (- (* b b) (* 4 a c))))
    (if (> d 0)
        (list
         (/ (+ (- b) (sqrt d)) (* 2 a))
         (/ (- (- b) (sqrt d)) (* 2 a)))
        (if (= d 0) 
            (list (/ (+ (- b) (sqrt d)) (* 2 a)))
            (list)))))

; Воспользуемся Алгоритмом Евклида
; Реализуем его при помощи хвостовой рекурсии
(define (my-gcd a b)
  (define (loop x y)
    (if (or (= 0 x) (= 0 y))
        0
        (if (> x y)
            (loop (- x y) y)
            (if (< x y)
                (loop x (- y x))
                x))))
  (loop a b))

; Реализация через cond
(define (my-gcd1 a b)
  (define (loop x y)
    (cond ((or (= 0 x) (= 0 y)) 0)
          ((> x y) (loop (- x y) y))
          ((< x y) (loop x (- y x)))
          (else x)))
  (loop a b))

(define (my-lcm a b)
  (/ (* a b) (my-gcd a b)))

(define (prime? n)
  (define (loop i)
    (if (not (or (= 0 (remainder n i)) (> (* i i) n)))
        (loop (+ 1 i))
        (not (= 0 (remainder n i)))))
  (and (loop 4) (not (= 1 n)) (not (< n 0))))
          
          
