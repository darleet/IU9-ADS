(define pi (* 4 (atan 1)))
(define e 2.718281828459045)

(define (circ-len r)
  (* 2 pi r))

(define (circ-area r)
  (* pi r r))

(define (rect-len a b)
  (* 2 (+ a b)))

(define (rect-area a b)
  (* a b))

(define (<> a b)
  (not (= a b)))

(define (signum x)
  (if (my-positive? x)
      +1
      (if (not my-positive? x)
          -1
          0)))

(define (my-positive? x)
  (> x 0))

(define zero -273.15)

(define (my-abs x)
  (if (> x 0)
      x
      (- x)))

(define (! n)
  (if (> n 0)
      (* (! (- n 1)) n)
      1))

(define (my-* x y)
  (if (> y 0)
      (+ (my-* x (- y 1)) x)
      0))

(define (my-odd? x)
  (if (= (remainder x 2) 1)
      #t
      #f))

(define (my-even? x)
  (if (= (remainder x 2) 0)
      #t
      #f))

(define (power b e)
  (if (= b 0)
      0
      (if (> e 0)
          (* (power b (- e 1)) b)
          (if (< e 0)
              (/ (power b (+ e 1)) b)
              1))))
  