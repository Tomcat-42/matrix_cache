from typing import Dict, Iterable, List, Any
import json

import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

from pprint import pprint as pp

NANO_SECONDS = 1e-9


def parse_bench_json(json_file_path: str) -> Dict[str, Any]:
    """
    Parse a JSON file into a dictionary.
    """
    with open(json_file_path) as json_data:
        data = json.load(json_data)
    return data["benchmarks"]


def parse_bench_dict(bench_dict: Dict[str, any]) -> Dict[str, Any]:
    """
    Parse a benchmark file into a list of dictionaries.
    """
    def get_meaningful_data(data: Dict[str, Any]) -> Dict[str, Any]:
        """
        Get the data we want from the dictionary.
        """
        size = int(data["run_name"].split("/")[-1])
        return {
            "repetitions": data["repetitions"],
            "iterations": data["iterations"],
            "size": size,
            "real_time": data["real_time"],
            "cpu_time": data["cpu_time"],
        }

    bench_mean, bench_max, bench_min, bench_median, bench_stddev, bench_cv = list(filter(lambda x: x["aggregate_name"] == "mean", bench_dict)), list(filter(
        lambda x: x["aggregate_name"] == "max", bench_dict)), list(filter(lambda x: x["aggregate_name"] == "min", bench_dict)), list(filter(lambda x: x["aggregate_name"] == "median", bench_dict)), list(filter(lambda x: x["aggregate_name"] == "stddev", bench_dict)), list(filter(lambda x: x["aggregate_name"] == "cv", bench_dict))

    name, time_unit = bench_mean[0]["name"].split(
        "/")[0], bench_mean[0]["time_unit"]

    final_dict = {
        "name": name,
        "time_unit": time_unit,
        "mean": list(map(get_meaningful_data, bench_mean)),
        "max": list(map(get_meaningful_data, bench_max)),
        "min": list(map(get_meaningful_data, bench_min)),
        "median": list(map(get_meaningful_data, bench_median)),
        "stddev": list(map(get_meaningful_data, bench_stddev)),
        "cv": list(map(get_meaningful_data, bench_cv)),
    }

    return final_dict


def plot_data(xs: Iterable[Iterable], ys: Iterable[Iterable], legends: List[str], colors: List[str], x_label: str, y_label: str, title: str, x_lim: int = None, y_lim: int = None) -> None:
    """
    Plot a graph.
    """

    plt.title(title)
    plt.xlabel(x_label)
    plt.ylabel(y_label)

    if x_lim:
        plt.xlim(0, x_lim)
    if y_lim:
        plt.ylim(0, y_lim)

    for x, y, color in zip(xs, ys, colors):
        plt.plot(y, x, color=color)

    plt.legend(legends)
    plt.show()


def plot_all_aggregations(bench_dict: Dict[str, Any], title: str) -> None:
    """
    Plot all the aggregations of a benchmark.
    """
    means = list(map(lambda x: x["real_time"] *
                 NANO_SECONDS, bench_dict["mean"]))
    maxes = list(map(lambda x: x["real_time"]*NANO_SECONDS, bench_dict["max"]))
    mins = list(map(lambda x: x["real_time"]*NANO_SECONDS, bench_dict["min"]))
    medians = list(map(lambda x: x["real_time"]
                   * NANO_SECONDS, bench_dict["median"]))
    stddevs = list(map(lambda x: x["real_time"]
                   * NANO_SECONDS, bench_dict["stddev"]))
    sizes = list(map(lambda x: x["size"], bench_dict["mean"]))

    plot_data([means, maxes, mins, medians, stddevs], [sizes] * 5, ["mean", "max", "min", "median", "stddev"],
              ["blue", "red", "green", "yellow", "purple"], "Size", f"Time (s)", title)


def plot_comparsion(bench_dict_a: Dict[str, Any], bench_dict_b: Dict[str, Any], title: str, field: str) -> None:
    """
    Plot the comparsion of two benchmarks
    """
    field_a = list(map(lambda x: x["real_time"]
                   * NANO_SECONDS, bench_dict_a[field]))
    field_b = list(map(lambda x: x["real_time"]
                   * NANO_SECONDS, bench_dict_b[field]))
    sizes = list(map(lambda x: x["size"], bench_dict_a[field]))

    plot_data([field_a, field_b], [sizes] * 2, ["Normal", "Transposed"],
              ["blue", "red"], "Size", f"Time (s)", title)


def draw_table(bench_dict: Dict[str, Any], title: str) -> None:
    """
    Draw a table with the data of a benchmark
    """
    means = list(map(lambda x: x["real_time"] *
                 NANO_SECONDS, bench_dict["mean"]))
    maxes = list(map(lambda x: x["real_time"]*NANO_SECONDS, bench_dict["max"]))
    mins = list(map(lambda x: x["real_time"]*NANO_SECONDS, bench_dict["min"]))
    medians = list(map(lambda x: x["real_time"]
                   * NANO_SECONDS, bench_dict["median"]))
    stddevs = list(map(lambda x: x["real_time"]
                   * NANO_SECONDS, bench_dict["stddev"]))
    cvs = list(map(lambda x: x["real_time"]*100.0, bench_dict["cv"]))
    sizes = list(map(lambda x: x["size"], bench_dict["mean"]))

    fig, ax = plt.subplots()

    # hide axes
    fig.patch.set_visible(False)
    ax.axis('off')
    ax.axis('tight')

    df = pd.DataFrame(zip(means, maxes, mins, medians, stddevs, cvs), columns=[
                      "mean (s)", "max (s)", "min (s)", "median (s)", "stddev (s)", "cv (%)"])
    df_r = df.round(decimals=3)

    ax.table(cellText=df_r.values, colLabels=df_r.columns,
             loc='center', colColours=["#BD93F9"] * len(df_r.columns), rowLabels=sizes, rowColours=["#BD93F9"] * len(df_r))

    ax.set_title(title)
    fig.tight_layout()

    plt.show()


def draw_table_comparsion(bench_dict_a: Dict[str, Any], bench_dict_b: Dict[str, Any], title: str) -> None:
    """
    Draw a table with the data of 2 benchmarksw
    """
    means_a = list(map(lambda x: x["real_time"] *
                       NANO_SECONDS, bench_dict_a["mean"]))
    means_b = list(map(lambda x: x["real_time"] *
                       NANO_SECONDS, bench_dict_b["mean"]))
    stddevs_a = list(map(lambda x: x["real_time"]
                         * NANO_SECONDS, bench_dict_a["stddev"]))
    stddevs_b = list(map(lambda x: x["real_time"]
                         * NANO_SECONDS, bench_dict_b["stddev"]))
    cvs_a = list(map(lambda x: x["real_time"]*100.0, bench_dict_a["cv"]))
    cvs_b = list(map(lambda x: x["real_time"]*100.0, bench_dict_b["cv"]))
    sizes = list(map(lambda x: x["size"], bench_dict_a["mean"]))

    fig, ax = plt.subplots()

    # hide axes
    fig.patch.set_visible(False)
    ax.axis('off')
    ax.axis('tight')

    df = pd.DataFrame(zip(means_a, means_b, stddevs_a, stddevs_b, cvs_a, cvs_b), columns=[
        "mean N(s)", "mean T(s)", "stddev N(s)", "stddev T(s)", "cvs N(s)", "cvs T(s)"])
    df_r = df.round(decimals=3)

    ax.table(cellText=df_r.values, colLabels=df_r.columns,
             loc='center', colColours=["#BD93F9"] * len(df_r.columns), rowLabels=sizes, rowColours=["#BD93F9"] * len(df_r))

    ax.set_title(title)
    fig.tight_layout()

    plt.show()


def draw_speedup_table(bench_dict_a: Dict[str, Any], bench_dict_b: Dict[str, Any], title: str):
    """
    Draw a table with the data of 2 benchmarksw
    """
    means_a = list(map(lambda x: x["real_time"] *
                       NANO_SECONDS, bench_dict_a["mean"]))
    means_b = list(map(lambda x: x["real_time"] *
                       NANO_SECONDS, bench_dict_b["mean"]))
    speedups = list(map(lambda x: ((x[1]/x[0])*100.0), zip(means_a, means_b)))
    sizes = list(map(lambda x: x["size"], bench_dict_a["mean"]))

    fig, ax = plt.subplots()

    # hide axes
    fig.patch.set_visible(False)
    ax.axis('off')
    ax.axis('tight')

    df = pd.DataFrame(speedups, columns=[
        "speedup (%)"])
    df_r = df.round(decimals=3)

    ax.table(cellText=df_r.values, colLabels=df_r.columns, cellLoc="center",
             loc='center', colColours=["#BD93F9"] * len(df_r.columns), rowLabels=sizes, rowColours=["#BD93F9"] * len(df_r))

    ax.set_title(title)
    fig.tight_layout()

    plt.show()


def plot_speedup(bench_dict_a: Dict[str, Any], bench_dict_b: Dict[str, Any], title: str):
    """
    Draw a plotwith the data of 2 benchmarks
    """
    means_a = list(map(lambda x: x["real_time"], bench_dict_a["mean"]))
    means_b = list(map(lambda x: x["real_time"], bench_dict_b["mean"]))
    speedups = list(map(lambda x: (x[1]/x[0])*100.0, zip(means_a, means_b)))

    sizes = list(map(lambda x: x["size"], bench_dict_a["mean"]))

    plot_data([speedups], [sizes], ["Speedup"],
              ["blue"], "Size", f"Speedup (%)", title)
