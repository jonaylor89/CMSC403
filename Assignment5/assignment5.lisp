
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
     
      (
        (> year 2018) 
        yearList
      )

      (
        (and (= (mod year 100) 0) (/= (mod year 400) 0))
        (nextYear yearList (+ year 4))
      )

      (
        T 
        (nextYear (nconc yearList (list year)) (+ year 4))
      )
    )
  )

  (nextYear '() 1800)
)

; 3)
(defun union- (l1 l2)
  "Return the union of two lists" 
  (cond 
    (
      (not l2)
      l1
    ) 

    (
      (not (member (first l2) l1))
      (append (union- l1 (rest l2)) (list (first l2)))
    )

    (
      T 
      (union- l1 (rest l2))
    )
  )
)

; 4)
(defun avg (aList)
  "Return average of a list using tail recursion"
  (cond 
    (
      (not aList) 
      NIL
    )
    (
      T
      (progn
        (defun avgHelper (partialList accum size)
          (cond
            (
              (not partialList) 
              (/ accum size)
            )
            (
              T
              (avgHelper (rest partialList) (+ accum (first partialList)) (+ size 1))
            )
          )
        )

        (avgHelper aList 0 0)
      )
    )
  )
)

; 5.)
(defun isType (dataType) 
  "Return anonymous function checking if a value is the dataType"
  #'(lambda (x) (typep x dataType ))
)

; 6.)
(defun taxCalculator (limit rate values)
  "Find taxes"
  (mapcar #'(lambda (x) 
                (cond 
                  (
                    (> x limit) 
                    (* x rate)
                  )
                )
              )
          values
  ) 
)

; 7)
(defun clean (aFunc aList)
  "Clean list using function (filter)"

  (cond
    (
      (not aList) 
      NIL
    ) 
    (
      (funcall aFunc (first aList))
      (cons (first aList) (clean aFunc (rest aList)))
    )

    (
      T 
      (clean aFunc (rest aList))
    )
  )  
)

; 8)
(defmacro threeWayBranch (x y toExecute)
 "Branching macro" 
  (cond
    ((> x y) (first toExecute))
    ((< x y) (second toExecute))
    (T (last toExecute))
  )
)
