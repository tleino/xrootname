# xrootname

*xrootname* sets X11 root window name (root window title) from an
**stdin** stream so that window managers such as
[mxswm](https://github.com/tleino/mxswm) can get a continuously updating
status line.

## Rationale

Performance. Obviously one could use xsetroot in a shell script loop for
achieving the same, but since a continuously updating status line is
often used for *monitoring* performance, the monitoring program itself
should not cause spikes to the measurements. Continuously re-launching a
program obviously is more costly and spiky in terms of measurements
than *xrootname*.
