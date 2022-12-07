(define (save-data var path)
  (call-with-output-file path
    (lambda (port)
      (write var port)
      (newline port))))

(define (load-data path)
  (call-with-input-file path
    (lambda (port)
      (let loop ((data (read port)))
        (if (not (eof-object? data))
            (begin (write data) (loop (read port)))
            (newline))))))

(load-data "1.txt")

(define (line-count path)
  (call-with-input-file path
    (lambda (port)
      (define (loop counter prev-newline?)
        (let ((symbol (read-char port)))
          (cond ((and (equal? symbol #\newline) (not prev-newline?))
                 (loop (+ 1 counter) (equal? symbol #\newline)))
                ((eof-object? symbol) counter)
                (else (loop counter (equal? symbol #\newline))))))
      (loop 0 #\newline))))
      
(line-count "1.txt")