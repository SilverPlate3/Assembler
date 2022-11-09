# Assembler

# Background 
I didn't know if I should upload this project, as its just a university assignment I encountered which I took totally off the rails...  
The original project was cool by itself as it asked us to build a 12-bit assembler. I just had one issue with it. It had to many guidelines.  
The question tells us: what data structures to use, how the assembler flow should work, what can we assume, etc'.  
So I have decided to create my own type of assembler, with unique techniques, data structures usage and most importantly the flow.  
I won't lie, <b>this was the worst mistake of my life</b>. Who am I to redesign an assembler... This made it nearly impossible.   
But as my mom told me when I was a child, "Finish what you started".  


# Key things I tried to implement 
- No memory leaks
- Concepts from the book "Clean Code" (I know main() itself doesn't look like it)
- Few neat techniques I learned while scrolling through the book "Understanding and Using C Pointers"
- Macro's for functions that may take different types of pointers.
- High cohesion (Yes, its an OOP term, but you get me).
- Diversity of data structures.


# Issues
- Both the .pdf (question) and .docx (side notes I made) are in Hebrew. Sorry none-Hebrew-speaking fellas.
- The question is 25 pages long with very "sophisticated" Hebrew terms. So even the Hebrew speakers may face difficulties.
- The Main() function is 215 lines long. (But remember its C).
- The program is pretty efficient except the 3 Symbols tables which are extremely not (But I was eager to implement Hash Tables).
