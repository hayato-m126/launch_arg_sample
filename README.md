# launch arg sample
This is demo package to describe lauch argument bug.

## problem
If string argement includes colon <span style="color: red; ">:</span> , launch process will die. 

![demo](./demo.gif)

## how to use

```shell
# launch process will die
ros2 launch launch_arg_sample sample.launch.py compare_str:="Hello World:"
```

```shell
# working
ros2 launch launch_arg_sample sample.launch.py compare_str:="Hello World"
```
