#C++ info and refactoring tool
A tool to get info from c++ code and to refactor it using [clang](http://clang.llvm.org/).

##Plan
- [x] Retrieve basic information about a symbol for specified file:column.
- [ ] Get all the files from a compilation database.
- [ ] Use `grep` and [LibTooling](http://clang.llvm.org/docs/LibTooling.html)'s
capabilities to find all instances of a specified symbol...
- [ ] ... and to rename it.
