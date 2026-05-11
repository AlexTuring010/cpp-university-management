# cpp-university-management

A **text-based university simulation** in C++ — you play as the department secretary. Hire professors, enrol students, create semesters and courses, assign teaching, run exams, advance to the next season, and check who can graduate. Built as a single CLI "game" loop with full referential integrity across the domain model.

University class project for the **Object-Oriented Programming** course at the University of Athens (Department of Informatics & Telecommunications). Solo project.

## What it does

`main` constructs a `Life` object, which owns a `Secretary`, which owns all the people and academic structure. `Life::service_player_commands()` is the REPL: read a line, dispatch.

```
                     ┌─────────────────────────┐
                     │           Life          │
                     │ (REPL + current season) │
                     └────────────┬────────────┘
                                  │ owns
                                  ▼
                     ┌─────────────────────────┐
                     │        Secretary        │
                     │  students     professors│
                     │  courses      semesters │
                     │  graduates              │
                     │  mandatory/optional sums│
                     └────────────┬────────────┘
                                  │ holds
                  ┌───────────────┼────────────────┐
                  ▼               ▼                ▼
            ┌─────────┐     ┌──────────┐     ┌────────────┐
            │ Student │     │Professor │     │  Semester  │
            └────┬────┘     └────┬─────┘     └─────┬──────┘
                 │ enrolled in   │ assigned to     │ contains
                 └───────┬───────┴───────┬─────────┘
                         ▼               ▼
                       ┌─────────────────┐
                       │     Course      │
                       │  mandatory/opt  │
                       │  points         │
                       └─────────────────┘
```

Sample command flow:

```
Enter a command: create student
Enter a command: create professor
Enter a command: create course
Enter a command: create semester
Enter a command: register …      # tie student → course
Enter a command: assign …        # tie professor → course
Enter a command: end season      # exams run, grades recorded
Enter a command: next season     # season flips (spring ⇄ winter)
Enter a command: print can graduate
```

Graduation rule: pass **all mandatory courses** and collect **≥ 30%** of total optional-course points.

## What was interesting

- **Relationship integrity on every update.** Changing one entity ripples to every related entity. If a course's semester is moved later, every enrolled student whose academic year no longer permits that course is automatically un-registered. Same for deletions — entities are cleanly detached from everything that referenced them, no dangling pointers.
- **`Secretary` as the only mutable god-object, by design.** The OOP-class spec asked for explicit secretary-mediated operations rather than entities mutating each other directly. Everything funnels through `Secretary` methods like `addCourseToSemester`, `assignProffessorToCourse`, `registerInCourse` — easier to enforce invariants in one place than scattered.
- **Two-pass exam logic.** `doTheExams(Season)` walks the season's courses, and the `doTheExams_helper` per-course pass writes grades and updates the per-student / per-course passed/failed tallies that `printStatistics` and `canGraduate` later read in O(1).
- **`Life` and `Secretary` cross-friended.** `friend class Life;` in `Secretary` lets the REPL layer reach private state during seasonal transitions without exposing those internals to every caller.

## Build & run

```bash
make
./build/my_program
```

Then type `help` for the command list. `import <file>` loads bulk data — see `test_files/` for the expected format (`students.txt`, `professors1.txt`, `courses1.txt`, `semesters1.txt`).

## Modules

| File | Purpose |
|---|---|
| `main.cpp` | Constructs `Life`, starts the REPL |
| `src/Life.cpp` | Command dispatch, season transitions, ANSI-coloured I/O |
| `src/Secretary.cpp` | Domain logic: create/update/delete + relationship maintenance + exams + statistics |
| `src/Student.cpp` / `src/Professor.cpp` / `src/Person.cpp` | Person hierarchy |
| `src/Course.cpp` / `src/Semester.cpp` | Academic structure |
| `src/Gender.cpp` | Enum-with-string-conversion helpers |
| `includes/*.hpp` | Public interfaces, plus `ErrorSignals.hpp` for thrown-value codes |
| `documentary/assignment_instructions.pdf` | Original assignment specification (Greek) |

## License

[MIT](LICENSE) — applies to my own code in this repo. Assignment-distributed materials retain their original course copyright.
