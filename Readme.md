# MLearner
Generic implementations of some fancy ML algorithms and examplatory usages.

## Building the Project
Compile this project using the provided shell script:
```
$ ./build.sh
```

## Examples

### Gene Clusterer
Let's try to find some structure in genes from dicty.
Their sequences can be found at [dictybase](http://dictybase.org/db/cgi-bin/dictyBase/download/blast_databases.pl).

To run this example, navigate to `./examples/gene_clusterer/` and generate your clusters using
```
./clusterer/clusterer <fasta file>
```
You can then do many analyses by running
```
./analyzer/analyzer <cluster file>
```
