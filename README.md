# LogicVerifier

## Introduction
LogicVerifier (LV) is a project prototype aims at providing logical verification on mathematical statement. It is found that there are overwhelming publication of scientific paper published with result that is wrong or misunderstood. For example, the papers related to P-vs-NP collected by https://www.win.tue.nl/~gwoegi/P-versus-NP.htm. Chance is that there could be a hidden gem within one of these paper. On the other hands, if all the paper claimed a false result, could we point out where it goes wrong and avoid those mistakes in the future? There are quite a lot of problem we would like to resolve in this project. 

## The Problems
### Open knowledge
First, it is quite impossible to find someone who has both the knowledge and patient to go through all these papers. Understanding these papers require board range of understanding in different subjects, including logics, abstract algebra, linear algebra, theoretical computer science, functional analysis, quantum computing, graph theory, just to name a few. Sure papers with significant and well known result are well verified by expert in the field that everyone could trust with. How about those papers that are hidden in the forest, not interested by the community or anyone, could we do something for them like at least verifying that what they proof is correct? Could we help young researcher in finding their logical error in their proof as soon as possible?

### Machine Verification
Second, it is impossible to eliminate human error. Be it the writer or the reader of the paper. What the author wrote could be slightly different from what the reader understood. That’s why scientific proof relies heavily on its logical validity. We use logic to provide a rigid and unarguable proof underneath. Sadly the reality is that for easy understanding and time consideration, scientific paper is written mostly in human language. Human language is ambiguous, sometimes our brains would help to “correct” and “make sense of” the language by unstated assumption and common sense. This could lead to serious problem if these assumption or common senses are wrong or not expected. Note that we are human and human makes mistakes. Furthermore, the weakness (and strength) of logics system is that if one step in the proof is wrong, everything follows are unsound.

### Searching
Third, sometimes it is difficult to search for existing result. A theory could have been proven with a completely different name in another completely different field. Could we aid researchers in locating these proofs easily and convince them that these result are correct without the need of background knowledge in the field?

### Optimisation
Forth, a proof may be too complicate to be understood. Could we simplify them? Whenever someone provides a new proof on a certain theory, could this new proof technique be applied on simplifying some other existing proofs that have similar proof structure?

### A Platform for Logic Verification
We would like to provide a platform for people to do logical reasoning without proofreading, for teachers streamlining homework checking on mathematical logic, for students to learn about logical reasoning in a responsive fashion.

## Design Goal
One goal of LV is to provided a centralised logic proof and verification system that is open to the public. LV has all the basic logic system predefined. User may work within a predefined logics system like propositional logic, first order logic, second order logic or user defined logic system with predefined or stored axiom and theorem and come up with proof for their own statement. These new proof by users would be verified and stored in database and open for other’s use, for example to quote, to reference, to build on top of. For the writer, all statements must be expressed in logical symbol without any confusion (We could probably provide template for writer to input logical proof statement). For readability, writer may also provide translation into human language (hopefully we could do something here to aids the translation). Since proofing a simple theory require a lot of basic axioms and some early results. This is such a huge wiki typed project that require input from expert of the field to build up a knowledge database of the world.

Eventually, we would like LV to work for all scientific publication that relies heavily on logical and mathematical proof. We would like to verify and convince everyone (even a layman) that a proof passed the LV verification is 100% correct without human error, nor the need of human verification.
