from setuptools import setup, find_packages
setup(
    name='tellopy',
    version='1.0',
    author='Alec Graves',
    author_email='alec@graves.tech',
    description='A simple package for controlling and viewing video from the DJI Tello',
    long_description=open('README.md').read(),
    long_description_content_type='text/markdown',
    url='https://github.com/alecGraves/telloc',
    packages=find_packages(),
    package_data={'telloc': ['libtellopy.so', 'libtellopy.dll']},
    include_package_data=True,
    classifiers=[
        'Development Status :: 3 - Alpha',
        'Programming Language :: Python :: 3',
        'License :: OSI Approved :: MIT License',
        'Operating System :: OS Independent',
    ],
)
