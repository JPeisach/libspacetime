# libspacetime
Library for timekeeping beyond Earth

## What is this?
This is a C library for date and time operations across multiple planets. The goal was initially to make working with the [Darian calendar](https://en.wikipedia.org/wiki/Darian_calendar) as easy as possible, but as I was doing some reading, I found that Thomas Gangale also considered a calendar system for [Jupiter](https://ops-alaska.com/time/gangale_jupiter/jupiter.htm), so I decided to lay out the foundation for planetary time.

Currently, the goal is to work with the Darian calendar, then other planets, if there are any existing calendar systems.

## Important Notes
- The Darian calendar is not "standard" by any means. The timekeeping method of MSD does appear to be used by NASA, but the calendar itself is not recognized officially. Same goes for any other "planetary systems".
- C standards - A lot of my work has been looking at existing implementations for [time and date functions in C](https://en.wikipedia.org/wiki/C_date_and_time_functions), and those were built upon standards. I currently lack the skills for timekeeping in general, and I knew nothing about POSIX.1 or ISO C standards before this. **I am currently just doing one function and operation at a time, and I cannot promise "similarity" to any standards. For example, glibc seems to do calculations for date and time under internal "timezone", but, as of writing, I am not there yet. Naming conventions may also differ. I would spend too much time worrying about trying to make things match as seamlessly to existing standards at this stage, that it is not worth it. So I am taking this as a learning process and will adjust things later.
- Library likely to change - see above. Also keep in mind that potentially the entire idea of timekeeping across planets, espeically if I go past Mars, could possibly be abstracted to like, any planet based on its orbit and length of day? Maybe this will end up being a "make your own planetary timekeeping" library. (Honestly, I hope not)
- Moving this into standards - I mean, it would be cool. I'll eventually come around to matching standards as best as possible, then maybe a proposal can be submitted? I don't know anything about the process.
