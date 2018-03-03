# ft_ls

## default flags
```
-l	List in long format.  (See below.)  If the output
	is to a terminal, a total sum for all the file
	sizes is output on a line before the long listing.

-R	Recursively list subdirectories encountered.

-a	Include directory entries whose names begin with a dot (.).

-r	Reverse the order of the sort to get reverse
	lexicographical order or the oldest entries first
	(or largest files last, if combined with sort by size

-t	Sort by time modified (most recently modified first)
	before sorting the operands by lexicographical order.
```

## bonus flags
```
-S	Sort files by size

-U	Use time of file creation, instead of last modification for
	sorting (-t) or long output (-l)

-d	Directories are listed as plain files (not searched recursively)

-f	Output is not sorted.  This option turns on the -a option.

-g	This option is only available for compatibility with POSIX;
	it is used to display the group name in the long (-l) format
	output (the owner name is suppressed).

-u	Use time of last access, instead of last modification of the
	file for sorting (-t) or long printing (-l)
```
