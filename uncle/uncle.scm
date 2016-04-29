; Caroline Danzi
; Dr. Zmuda
; CSE 465
; Starter file from Dr. Zmuda
; Great Uncle/Aunt Problem

; A list of the parent relationships (parent child)
(define parents '((male1 male2)(male1 male3)(male1 female2)
(female1 male2)(female1 male3)(female1 female2)(male2 male4)
(male2 male8)(female3 male4)(female3 male8)(male4 female7)
(male4 male7)(female6 female7)(female6 male7)(male8 female9)
(female8 female9)(male3 female5)(male3 male5)(female4 female5)
(female4 male5)))

; A list of all the people who are married (husband wife)
(define married '((male1 female1)(male2 female3)(male3 female4)
(female2 male6)(male4 female6)(male8 female8)(male7 female10)))

; Returns true if uncle is a great uncle or aunt to kid
(define (greatUncle lst uncle kid)
	; Overall structure: find the parents of the uncle and their spouse, then check the 
	; third generation down to see if the kid is there
	(if (member kid (getNextGeneration parents 
	(getNextGeneration parents 
	; Note: remove the uncle and their spouse from the first generation we get 
	; First generation from great uncle's parents is the great uncle and their siblings
	(remove (getSpouse married uncle)
	(remove uncle (getNextGeneration parents (getAuntUncleParents lst married uncle))))))) #t #f)
)

; Gets all the parents of the great uncle and their spouse
(define (getAuntUncleParents parents married uncle)
	; append the list of the uncle's parents to the aunt's parents
	(append (getParents parents uncle) (getParents parents (getSpouse married uncle)))
)

; If the person is married, return their spouse
; otherwise, return false
(define (getSpouse married person)
	(COND
		((NULL? married) #f)
		; Check both elements in each marriage pair
		((EQUAL? (cadar married) person) (caar married))
		((EQUAL? (caar married) person) (cadar married))
		(else (getSpouse (cdr married) person))
	)
)

; Creates a list of the kid's parents
(define (getParents parents kid)
	(COND
		((NULL? parents) '())
		; If the second element in the head of the list (the kid) equals the kid,
		; Add the first element in the head of the list (the parent) to the list we are creating
		((EQUAL? (cadar parents) kid) (cons (caar parents) (getParents (cdr parents) kid)))
		(else (getParents (cdr parents) kid))		
	)
)

; Creates a list of the parent's children
(define (getKids parents parent)
	(COND
		((NULL? parents) '())
		((EQUAL? (caar parents) parent) (cons (cadar parents) (getKids (cdr parents) parent)))
		(else (getKids (cdr parents) parent))
	)
)

; Removes element from list (used to remove great uncle from list of siblings)
(define (remove elmt lst)
	(COND
		((NULL? lst) '())
		((EQUAL? elmt (car lst)) (remove elmt (cdr lst)))
		(else (cons (car lst) (remove elmt (cdr lst))))
	)
)

; Gets all the children of all the people in the current generation list
(define (getNextGeneration parents currentGen)
	(COND
		((NULL? currentGen) '())
		(else (append (getKids parents (car currentGen)) (getNextGeneration parents (cdr currentGen))))
	)
)

(newline)
(display (greatUncle parents 'male6 'female7)) ; #t
(newline)
(display (greatUncle parents 'male6 'male8)) ; #f
(newline)
(display (greatUncle parents 'female7 'male3)) ; #f
(newline)
(display (greatUncle parents 'female4 'female7)) ; #t
(newline)
(display (greatUncle parents 'female4 'male3)) ; #f
(newline)
(display (greatUncle parents 'male3 'male7)) ; #t
(newline)
(display (greatUncle parents 'male6 'female7)) ; #t
(newline)
(display (greatUncle parents 'female7 'male6)) ; #f
(newline)
(display (greatUncle parents 'male5 'female8)) ; #f
(newline)
(display (greatUncle parents 'male5 'male8)) ; #f
(newline)
(display (greatUncle parents 'male8 'female8)) ; #f
(newline)
,exit