(define (factorize expr)
  (let ((a (cadr (cadr expr)))
        (b (cadr (caddr expr))))
    (if (and (= (caddr (cadr expr)) 2) (= (caddr (caddr expr)) 2))
        (factorize-2 expr a b)
        (factorize-3 expr a b))))

(define (factorize-2 expr a b)
  `(* (- ,a ,b) (+ ,a ,b)))

(define (factorize-3 expr a b)
  (let ((sign (car expr)))
    `(* (,sign ,a ,b) (+ (- (expt ,a 2) (* ,a ,b)) (expt ,b 2)))))

; Тестирование

(define factorize-tests
  (list (test (factorize '(- (expt x 2) (expt y 2)))
              '(* (- x y) (+ x y)))
        (test (factorize '(- (expr x 3) (expr y 3)))
              '(* (- x y) (+ (- (expt x 2) (* x y)) (expt y 2))))))

(run-tests factorize-tests)

(factorize '(- (expt x 2) (expt y 2)))
(factorize '(- (expt (+ first 1) 2) (expt (- second 1) 2)))

(eval (list (list 'lambda 
                  '(x y) 
                  (factorize '(- (expt x 2) (expt y 2))))
            1 2)
      (interaction-environment))