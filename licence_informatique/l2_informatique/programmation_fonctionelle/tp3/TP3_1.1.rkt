(define(moyenne l)
  (cond
    ((null? l)'())
    ((= (length l) 1)(car l))
    (else(/(somme l)(length l)))
    )
  )

(define(somme l)
  (cond
   ((null? (cdr l))(car l))
   (else(+(car l)(somme (cdr l))))
   )
  )
(display "1) Moyenne : ")
(newline)

(moyenne '(5 5 15 15))

(display "---------------------------")
(newline)

(display "2) Pourcentage de notes supérieures ou égales à la moyenne : ")
(newline)

(define n 0)
(define m (moyenne '(5 5 15 15)))

(define(taux-notes-sup l)
  (cond
    ((null? l)0)
    ((>= (car l) m)(+(taux-notes-sup (cdr l)) 1))
    (else(taux-notes-sup (cdr l)))
    )
  )

(define (nb-notes-sup l)
  (*(/(taux-notes-sup l)(length l))100)
  )
   
(nb-notes-sup '(7 8 5 12 19 20))


  
  
  

