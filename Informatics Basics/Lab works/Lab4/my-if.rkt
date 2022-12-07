(define-syntax my-if
  (syntax-rules ()
    ((_ predicate then else)
     (let ((a (delay then))
           (b (delay else)))
       (or (and predicate (force a)) (force b))))))

(my-if #t 1 (/ 1 0))
(my-if #f (/ 1 0) 1)