
; 1.)
(defun myList () 
  "Return the magical list"

  ; Just gotta quote things so they're data
  '(4 (7 22) "art" ("math" (8) 99) 100)
)

; 2.)
(defun leapYear ()
  "Return the leap years between 1800 to 2018"    

  (defun nextYear (yearList year end)
   "Appends the next leap year to yearList until 2018"

    (cond 
      ( ; If the year is greater than the end then return the complete list
        (> year end) 
        yearList
      )

      ( ; Else if it fits this special case than add for and keep going recursively
        (and (= (mod year 100) 0) (/= (mod year 400) 0))
        (nextYear yearList (+ year 4) 2018)
      )

      ( ; By default, add the year to the yearList, add 4, and recursively move on
        T 
        (nextYear (nconc yearList (list year)) (+ year 4) 2018)
      )
    )
  )

  ; Start the recursion with an empty list and the start year
  (nextYear '() 1800 2018)
)

; 3)
(defun union- (l1 l2)
  "Return the union of two lists" 

  (cond 
    ( ; If the second list is empty then exit returning the first list
      (not l2)
      l1
    ) 

    ( ; Else if the first element in the second list isn't in the first then add it
      ; and find the union of the first list with the rest of the second
      (not (member (first l2) l1))
      (append (union- l1 (rest l2)) (list (first l2)))
    )

    ( ; Else, find the union of the first list and the rest of the second
      T 
      (union- l1 (rest l2))
    )
  )
)

; 4)
(defun avg (aList)
  "Return average of a list using tail recursion"

  (cond 
    ( ; If the list is empty then just return
      (not aList) 
      NIL
    )
    ( ; Else,
      T
      (progn

        (defun avgHelper (partialList accum size)
         "A helper function to keep track of the accumulation of the sum and the size recursively"

          (cond
            ( ; If the list is empty, calculate the average
              (not partialList) 
              (/ accum size)
            )
            ( ; Else, add the first element to the accumulator, increment the size, and move on with rest of the list
              T
              (avgHelper (rest partialList) (+ accum (first partialList)) (+ size 1))
            )
          )
        )

        ; Kick things off
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

  ; Just map a lambda that checks if a value is greater than
  ; limit and multiplies it accordingly 
  (mapcar #'(lambda (x) 
                (cond 
                  ( ; Check is greater than limit and multiply
                    (> x limit) 
                    (* x rate)
                  )
                  ( ; Otherwise return the original value
                    T
                    x
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
    ( ; If list is empty, return NIL
      (not aList) 
      NIL
    ) 
    ( ; Else if function on the first element returns T
      ; and append it to a new list if returns T
      (funcall aFunc (first aList)) ; Call function on first
      (cons (first aList) (clean aFunc (rest aList))) ; append to the rest
    )

    ( ; Else, just pass on the rest of the list
      T 
      (clean aFunc (rest aList))
    )
  )  
)

; 8)
(defmacro threeWayBranch (x y toExecute)
 "Branching macro" 

  ; Helper function to execute a list of statements
  (defun executeList (aList)
    (cond
      ( ; If the list is empty, return NIL
        (not aList) 
        NIL
      )

      ( ; Else evaluate the first element in the list pass on the rest
        T 
        (progn
          (eval (first aList)) ; Eval first element
          (executeList (rest aList)) ; Pass on the rest
        )
      )
    )  
  )

  (cond
    ; If x < y execute the first sublist of statements
    ((< x y) (executeList (first toExecute)))

    ; Else if x > y execute the second sublist of statements
    ((> x y) (executeList (second toExecute)))

    ; Else execute the third sublist of statements
    (T (executeList (third toExecute)))
  )
)

