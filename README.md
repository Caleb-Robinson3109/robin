# Robin

Robin is a **functional-first programming language** with a familiar **C/C++-style syntax** that makes functional programming more approachable — especially for developers coming from imperative backgrounds.  

Instead of relying on **monads** to handle side effects, Robin uses **explicit scopes** that broaden or restrict your abilities. This makes code clarity a priority, while still enforcing functional purity by default.

---

## ✨ Key Ideas

- **Functional by default** – Pure functions are the baseline.  
- **Explicit scopes for side effects** – Open a scope like `IO {}` to allow output, or `State {}` for mutation.  
- **Compile-time enforcement** – Doing an effect in the wrong scope? Robin won’t compile.  
- **Familiar syntax** – C/C++-style function definitions and block syntax for easier learning.  
- **Nested scopes** – Scopes can be combined or nested for advanced effects.  

---

## 📦 Example

```robin
main -> int
{
    IO {
        output "Hello_World" ;
    }
    return 0 ;
}
