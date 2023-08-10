(defun task1 (l_st sym) 
(cond ((null l_st) nil)
((numberp (car l_st))  (cons (if (>= (car l_st) 0) (list (car l_st) (car sym)) (car l_st)) (task1 (cdr l_st) sym)) )
(t (cons (car l_st) (task1 (cdr l_st) sym)))
)
)
(task1 '(-1 d 6 -3 a 0) `(*))


(defun task2 (x y)
(cond ((null x) y)
(T (cons (car x) (task2 y (cdr x))))
)
)
(task2 '(1 2 3 4 5 6 7 8) '(a s d f))

(defun task3 (x)
(cond ((null x) x)
((null (butlast x)) x)
(T (cons (+ (car x) (car (last x))) (task3 (cdr (butlast x)))))
)
)

(task3 '(1 -2 -3 4 5 6 -7 8 9))