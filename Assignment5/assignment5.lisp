
; 1.)
(defun myList () 
  "Return the magical list"
  '(4 (7 22) "art" ("math" (8) 99) 100)
)

; 2.)
(defun leapYear ()
  "Return the leap years between 1800 to 2018"    

  (defun nextYear (yearList year)
    (cond 
     
      ((= year 2018) (yearList))

      ((and (= (mod year 100) 0) (= (mod year 400) 0))
        (nextYear yearList (+ year 4))
      )

      (T 
        (progn 
          (append yearList year)
          (nextYear yearList (+ year 4))
        )
      )
    )
  )

  (nextYear () 1800)
)

; 3
(defun union- (l1 l2)
  "Return the union of two lists" 

)

; 4
(defun avg (aList)
  "Return average of a list using tail recursion"
  (if (= aList NIL) NIL
    (defun avgHelper (partialList accum size)
      (if (= partialList NIL) NIL
        (progn 
          (+ accum (car partialList))
          ()
        )
      )
    )

    (avgHelper aList 0 0)
  )
)

; 5.)
(defun isType (dataType) 
  "Return anonymous function checking if a value is the dataType"
  #'(lambda (x) (= dataType (type-of x)))
)

; 6.)
(defun taxCalculator (limit rate values)
  "Find taxes"
  (map values (lambda (x) 
                (if (> x limit) (* x rate))
              )
  ) 
)

; 7
(defun clean (aFunc aList)
  "Clean list using function"
  (map aList (lambda (x) )
   
  ) 

)

; 8
(defmacro threeWayBranch (x y toExecute)
 "Branching macro" 
 
)
