(load "trace.rkt")
(load "unit-test.rkt")

(define (convert seq)
  (cond ((vector? seq) (vector->list seq))
        ((string? seq) (string->list seq))
        (else seq)))

(define (convert-reverse type seq)
  (cond ((equal? type 'vector) (list->vector seq))
        ((equal? type 'string) (list->string seq))
        (else seq)))

(define (type? seq)
  (cond ((vector? seq) 'vector)
        ((string? seq) 'string)
        (else 'list)))

(define (ref seq-input . ident)
  (let ((seq (convert seq-input))
        (index (car ident))       ; индекс для поиска/вставки
        (element (cdr ident)))    ; элемент для вставки
    (if (null? element)
        (ref-find seq index)
        (ref-insert seq index element (type? seq-input)))))

(define (ref-find seq index)
  (define (loop seq step)
    (if (= step index)
        (car seq)
        (loop (cdr seq) (+ 1 step))))
  (loop seq 0))

(define (ref-insert seq index element seq-type)
  (let ((status
         (and (equal? seq-type 'string)
              (not (char? (car element))))))
    (define (loop seq-head seq-tail step)
      (cond (status (not status))
            ((= step index)
             (convert-reverse
              seq-type
              (append seq-head element seq-tail)))
            ((not (null? seq-tail))
             (loop
              (append seq-head (list (car seq-tail)))
              (cdr seq-tail)
              (+ 1 step)))
            (else (not (null? seq-tail)))))
    (loop '() seq 0)))

   
(ref '(1 2 3) 1 0)  
(ref #(1 2 3) 1 0) 
(ref #(1 2 3) 1 #\0)
(ref "123" 1 #\0)   
(ref "123" 1 0)     
(ref "123" 3 #\4)    
(ref "123" 5 #\4)    