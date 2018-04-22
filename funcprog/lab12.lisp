(setq IN '(a b c d e f g h i j k l))
(setq IR '(1 2 4 6 8))

(defun f (list inrem)
  (loop
     for item in list and index from 1
     unless (member index inrem)
     collect item))
(print (f IN IR))

(setq la '(a b c d e f g h i j k l m n))
(setq indx '(1 3 4 6 8 9))
(setq curpos 1)

(defun fx (la  indx  curpos)
    (cond 
        ((null la) nil)
        ((null indx) la)
        ((equal curpos (car indx))
            (fx (cdr la) (cdr indx)  (+ curpos '1)))
        (t (cons (car la) (fx (cdr la) indx (+ curpos '1))))
    )
)

(print (f la indx curpos))

(setq la '(a b c d e f g h i j k l m n))
(setq indx '(1 3 4 6 8 9))
(setq curpos 1)

(defun ft (la  indx  curpos)
    (cond 
        ((null la) nil)
        ((null indx) la)
        ((equal curpos (car la))
            append(append(indx la) (ft (cdr la) curpos )))
        (t (cons (car la) (ft (cdr la) indx curpos)))
    )
)

(print (f la indx curpos))

