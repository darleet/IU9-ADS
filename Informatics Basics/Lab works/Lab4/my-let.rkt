(define-syntax my-let
  (syntax-rules ()
    ((_ ((var value) ...) body ...)
     ((lambda (var ...) body ...) value ...))))

(define-syntax my-let*
  (syntax-rules ()
    ((my-let* () body ...)
     (my-let () body ...))
    ((my-let* ((var value)) body ...)
     (my-let ((var value)) body ...))
    ((my-let* ((var value) . other) body ...)
     ((lambda (var) (my-let* other body ...)) value))))

(my-let ((a 10))
        a)

(my-let* ((a 10)
          (b (+ a 2)))
         b)