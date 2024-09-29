(load "libcalc.ss");
(load "grafcalc.ss")


(define (add a b)
  (if(non_zero? b)
     (add(incrementer a)(decrementer b))a))
(add 3 4)

(define (sou a b)
  (if(non_zero? b)
     (sou(decrementer a)(decrementer b))a))
(sou 5 6)


(define(mul a b)
  (if(non_zero? (decrementer b))
     (add a (mul a (decrementer b))) a))

(define(div a b)
  (if(sup_egal? a b)
     (add 1(div(sou a b) b))0))
  