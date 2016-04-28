(define parents '((a b)(b c)(c d)))

(define (greatUncle lst uncle kid)
	(COND
		((NULL? lst) #f)
		((EQUAL? (car lst) (list uncle kid)) #t)
		(else (greatUncle (cdr lst) uncle kid))
	)
)

(display (greatUncle parents 'a 'b))
(newline)
(display (greatUncle parents 'b 'b))
(newline)
(display (greatUncle parents 'c 'd))
(newline)
(display (greatUncle parents 'd 'c))
(newline)

,exit
