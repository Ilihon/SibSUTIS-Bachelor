
(caar(cddr(car(cdddr(car '(( 1 2 3 ( 4 5 (*)))))))))

(append '(4 5 6) '()'(()))


(cons '(1 2) 3 )

(list '(1 2) 3)


(defun swapList(list1)
		(append (butlast list1 2) (last list1) (last (butlast list1))))


(swapList '(1 2 3 4 5))