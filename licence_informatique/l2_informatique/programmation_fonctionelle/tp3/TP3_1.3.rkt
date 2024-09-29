;version liste ordonnée
(define comptebon
  (lambda (N Lnb)
    (cond ((zero? N)'())
          ((null? Lnb)#f)
          ((< N (car Lnb)) #f)
           ((= N (car Lnb)) (list N))
           (else(let ((sol-partielle(comptebon(- N(car Lnb))(cdr Lnb))))
                  (if sol-partielle
                      (cons (car Lnb) sol-partielle)
                      (comptebon N (cdr Lnb))))))))
                                       
                                       
        

(comptebon 7 '(2 8))

(comptebon 21 '(1 1 3 5 7 10 12 15))