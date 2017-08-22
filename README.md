erluid
======

UUID functions for Erlang/OTP implemented as C++ NIFs.

example usage
-------------

Just add it to your rebar.config

```
{deps, [
  ...
  {erluid, {git, "https://github.com/cieplak/erluid.git", {branch, "master"}}},
  ...
```

and fire up a shell

```
$ rebar3 shell

1> Uuid = uuid:generate().
<<"f6b911b0-9031-421a-a346-b054120213ef">>

2> Id = uuid:generate_base58().
<<"jAvbw6ih7LHe9iFMpo9XKD">>

3> uuid:base58_decode(Id).
<<"9695c488-b884-4984-b294-5fabaefb4e5f">>

4> uuid:base58_encode(Uuid).
<<"wt3XZGQsZPrwCVzFoHjUfk">>

```

supported operating systems
---------------------------

FreeBSD.

Modify line 1 ("`INCLUDES = ...`") in `c_src/Makefile` to point to your C++ headers if it doesn't
compile.
