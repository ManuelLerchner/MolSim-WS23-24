import subprocess

SCRIPT_TEMPLATE = """#!/bin/bash

#SBATCH -J RayleighTaylor{{NUM_THREADS}}Threads
#SBATCH -o ./%x.%j.%N.out
#SBATCH -D ../MolSim-WS23-24/build/project/
#SBATCH --get-user-env
#SBATCH --clusters={{CLUSTER}}
#SBATCH --partition={{PARTITION}}
#SBATCH --mail-type=all
#SBATCH --mem=2000mb
#SBATCH --cpus-per-task={{NUM_THREADS}}
#SBATCH --mail-user=tobi.eppacher@gmail.com
#SBATCH --export=NONE
#SBATCH --time=00:30:00

OMP_NUM_THREADS={{NUM_THREADS}} ./MolSim ../../input/fluid_mixing/fluid_mixing_3d.xml
"""


def launch_job(name, num_threads, cluster, partition):
    script = SCRIPT_TEMPLATE.replace("{{NUM_THREADS}}", str(num_threads))
    script = script.replace("{{CLUSTER}}", cluster)
    script = script.replace("{{PARTITION}}", partition)
    with open(name+"_"+str(num_threads)+".sh", "w") as f:
        f.write(script)
    subprocess.call(["sbatch", "job.sh"])


if __name__ == "__main__":
    for num_threads in [1, 2, 4, 8, 16, 56, 96]:

        cluster, partition = ("serial", "serial_std") if num_threads <= 28 else (
            "inter", "teramem_inter")

        launch_job("parallel_rayleigh", num_threads, cluster, partition)
