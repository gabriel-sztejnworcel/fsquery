# FSQuery

Query your file system using SQL syntax

### Prerequisites

Linux, g++ with c++14 support, gnu readline library (used for the shell)

### Installing

```
make
```

### Examples

```
$ ./fsquery

fsquery> select TMP.* from '/tmp' TMP where TMP.extension <> 'txt' and TMP.size > 3000

fsquery> select T.* from '/home/gabriel/fsquerytest/dir2' T, '/home/gabriel/fsquerytest/dir1' TT where T.name = TT.name

fsquery> select T.name, T.extension from (select TI.* from '/home/gabriel/fsquerytest/dir2' TI where TI.extension = 'txt') T
```

### Important!

This is work in progress, it still lacks many of the planned features and it wasn't properly tested yet.

At the moment, the only attributes that can be queried are full path, file name, extension and file size. Table aliases must be provided everywhere (I hope to change this soon).

### Currently working on...

An option to embed fsquery queries in shell scripts (using a separate command line utility)
