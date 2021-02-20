# Enigma
Second Semester Project for my University Course named "Algorithm and Data Structure"

The task is to implement a variant of an Enigma machine which encrypts messages in an alphabet consisting of n letters denoted by numbers {1,2,...,n}. Symbol 0 ends the message.

Rotors Wx={wx, 0, wx, 1,...,wx, n}and reflectors Ry={ry, 0, ry, 1,...,ry, n} are given as permutations of numbers {1,2,...,n} and simulate mechanical parts that can be used by an operator. The internal "wiring" of these parts does not change.

Typing a letter into the input encrypts it by passing it through the rotors into reflector and back through the rotors in the inverse sequence, as seen here. A stationary sequence of rotors and a reflector represent a simple substitution cipher, it is their movement which makes the decoding chalenging.

Each rotor can move counterclockwise by at most one step during each encoding. The first rotor moves before every encoding; therefore if the initial position of this single rotor is denoted by the last letter of the alphabet (i.e. n, see example I) the first letter is encoded according to substitutions as stated in the rotor's definition.
Further rotors move according to rules outlined in scetion "Turnover notch positions" of this link and this section. Additional information about double stepping can be found here.

In case there are more than 3 rotors only the first 3 rotate.

Input can be thought as divided into two parts: definitions of pieces of the machine and p instructions how to encode a given message using some of those parts. Before encoding a message the machine is assembled from k out of m rotors and a single reflector (out of l) and the rotors are set to some initial positions.

