^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Change log for unique_identifier repository
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

1.0.1 (2013-03-25)
-------------------

 * **unique_id**: fix catkin Python install problem [4]_.

1.0.0 (2013-03-18)
-------------------

 * Convert to catkin for Hydro [1]_.
 * Make **unique_identifier** into a metapackage, depending on the
   **uuid_msgs** and **unique_id** packages. It should only be used
   for dependencies in dry stacks. Wet packages will depend directly
   on **uuid_msgs** and **unique_id**.

0.9.0 (2013-01-03)
------------------

 * Initial release to Groovy.
 * Add support to **unique_id** for C++ interface using boost uuid
   package.

0.8.0 (2012-07-19)
------------------

 * Initial release to Fuerte.
 * **uuid_msgs** provides uuid_msgs/UniqueID message.
 * **unique_id** package supports Python interface based on standard
   uuid package, but no C++ API yet.

Issues
======
.. [1] `issue #1 <https://github.com/ros-geographic-info/unique_identifier/issues/1>`_
.. [4] `issue #4 <https://github.com/ros-geographic-info/unique_identifier/issues/4>`_
