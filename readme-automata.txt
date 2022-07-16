The program starts by reading in a data file specified on the command line that 
contains the tuple that represents a DFA, where Q is the set of states, E is the alphabet, 
q is the initial state, F is the set of final states, and D is the set of transition 
functions as shown in the example below:

Q={q0,q1,q2,q3,q4,q5}
E={0,1}
q={q0}
F={q3,q4}
D=
{
(q0,0)->(q1)
(q0,1)->(q2)
(q1,0)->(q2)
(q1,1)->(q3)
(q2,0)->(q2)
(q2,1)->(q4)
(q3,0)->(q3)
(q3,1)->(q3)
(q4,0)->(q4)
(q4,1)->(q4)
(q5,0)->(q5)
(q5,1)->(q4)
}
