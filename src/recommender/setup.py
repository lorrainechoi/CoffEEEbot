from distutils.core import setup
from catkin_pkg.python_setup import generate_distutils_setup

# fetch values from package.xml
setup_args = generate_distutils_setup(
    packages=['recommender'],
    package_dir={'': 'src'},
    requires=['std_msgs', 'rospy', 'pandas', 'psycopg2', 'datetime']
)

setup(**setup_args)
