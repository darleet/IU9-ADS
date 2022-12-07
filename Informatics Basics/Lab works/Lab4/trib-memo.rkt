(define trib-memo
  (let ((memo-res '()))
    (lambda (n)
      (let* ((step-res (assoc n memo-res)))
        (if step-res
            (cadr step-res)
            (let ((new-res
                   (cond ((<= n 1) 0)
                         ((= n 2) 1)
                         (else (+ (trib-memo (- n 3))
                                  (trib-memo (- n 2))
                                  (trib-memo (- n 1)))))))
              (set! memo-res (cons (list n new-res) memo-res))
              (display memo-res)
              (newline)
              new-res))))))

(trib-memo 10)