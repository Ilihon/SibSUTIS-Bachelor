(CAR(CDR(CADAAR'(((1 (2 *)) 3) 4))))

(cons nil nil) 

(cons 1 (cons '(2 3) nil))
(LIST 1 (LIST 2 3))

(DEFUN ZAMENA (l)
(APPEND (last l) (CDR (butlast l)) (list (CAR l)))
)
(ZAMENA '(1 2 3 4 5 6))