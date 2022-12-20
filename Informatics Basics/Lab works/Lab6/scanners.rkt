#|
<Expression> ::= <Sign> <Number> | <Number>
<Number> ::= [0...9] | [0...9] <Number> | <Number> "." <Number>
<Sign> ::= "+" | "-" | <Empty>
<Empty> ::=
|#

(define (scan str)
  (define stream
    (make-stream (string->list str))))

(call-with-current-continuation
 (lambda (c) (set! break c)))

(define (number-

(define (check-frac string)
  (let ((