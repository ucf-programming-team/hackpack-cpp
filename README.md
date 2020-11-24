# UCF PT C++ Hackpack

## style
- use only the `#define`s and `typedef`s in the [template](https://github.com/ucf-programming-team/hackpack-cpp/blob/master/content/contest/template.cpp)
- run the formatter on any code you commit (`make format`)
    - you may need to install clang-format (`sudo apt install clang-format-10`)
- name files in upper camel case

## building PDF
The three dependencies for making the PDF are LaTeX, Python, and Make.
To build the hackpack PDF, go to the base directory and run `make kactl`.

## building snippets
To make/update the snippets, you just need to run `make snippets`, and it will assemble all of the snippets for you in `cpp.json` or `java.json`.

VSCode's soft tabs should match whatever style of tabs you're using. So, if you were using 2 spaces, all of the code that gets imported via snippet should also be in 2 spaces.

![snippet](https://user-images.githubusercontent.com/30928035/93427043-1f731600-f88b-11ea-8b77-64aa6537b70e.gif)

To use the snippets, find the C++ snippet file in VSCode (File->Preferences->User Snippets->cpp.json) and copy-paste the `cpp.json` file in `snippets/` into there.

## contents/to-do
check = code written

bold = code written and untested

- contest
    - [ ] template
        - [x] fast IO
        - [ ] `#define`s and `typedef`s (now `using`)
    - [ ] .bashrc
    - [ ] stupid mistakes
- misc
    - [x] **atharva's K-D vector thing** (does this need to be tested?)
    - [ ] hash set
        - [ ] other useful stuff from PBDS and how to use them
    - [x] **submasks in 3^n** (does this need to be tested?)
- structures
    - [x] BIT
    - [x] benq's K-D BIT???
    - [ ] treap
        - [ ] implicit
        - [ ] explicit
    - [ ] splay tree
        - [ ] implicit
        - [ ] explicit
    - [ ] link cut tree
    - [ ] segment tree 
        - [ ] seg tree beats
        - other wacky seg trees
    - [x] DSU
    - [ ] min queue
    - [ ] min stack
    - [x] RMQ (generic comparator)
    - [ ] wavelet tree
    - [ ] dominator tree (???)
- strings
    - [ ] aho corasick
    - [ ] eertree
    - [ ] hashing stuff
        - [ ] rolling hash
        - [ ] prefix hash stuff
        - [ ] codeforces proof stuff
    - [ ] KMP
    - [ ] manacher's (gross)
    - [x] z values
    - [ ] suffix array
- graph
    - [ ] binary lifting
    - [ ] HLD
    - [ ] centroid decomp
    - [ ] 2CC (BCC)
        - bridges and art. points
    - [ ] SCC
        - [ ] tarjan 
        - [ ] kosaraju (easy to type)
    - [ ] 2SAT
    - [x] dijkstra
    - [ ] bellman ford
    - [ ] floyd warshall
    - flow
        - [ ] dinic
        - [ ] MCMF
        - [ ] hungarian
- math
    - [ ] FFT
        - [ ] NTT with same code but also fast???
    - [ ] CRT
    - [ ] totient
    - [x] prime sieve
        - [x] ~~linear sieve?~~ segmented sieve
    - [ ] fractions
        - [x] **fraction struct**
        - [x] **fraction compare** (in fraction struct)
            - should this be in it's own file too?
        - [ ] fraction binary search
    - [ ] euclidean algo (GCD)
        - [ ] non prime mod inverse
    - [ ] pollard rho
    - [ ] primality testing
        - [ ] fermat
        - [ ] miller rabin (deterministic bases for longs)
    - [ ] primitive root
    - [ ] gaussian
    - [ ] big int???
        - atharva's code is wicked long
- geometry
    - [ ] vector
    - [ ] segment
    - [ ] circle
    - [ ] convex hull
    - [ ] polygon
        - [ ] rotation/translation?
        - [ ] clipping?
    - other geo stuff
