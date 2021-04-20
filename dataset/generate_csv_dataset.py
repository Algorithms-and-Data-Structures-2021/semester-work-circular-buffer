import random
import argparse
import csv
from faker import Faker

fake = Faker()


DEFAULT_DESCRIPTION = 'CSV dataset generator script.'
DEFAULT_SAMPLES = 100
DEFAULT_TYPE = 'int'
AVAILABLE_TYPES = {'str', 'int'}


def parse_args():
    parser = argparse.ArgumentParser(description=DEFAULT_DESCRIPTION)

    parser.add_argument('output',
                        type=str,
                        help='output CSV file, e.g. data/output.csv')

    parser.add_argument('--samples',
                        type=int,
                        default=DEFAULT_SAMPLES,
                        help='number of samples to generate '
                             '(default: {})'.format(DEFAULT_SAMPLES))

    parser.add_argument('--data_type',
                        type=str,
                        default=DEFAULT_TYPE,
                        help=f'type of samples\' to generate '
                             f'(available types: {AVAILABLE_TYPES}) '
                             f'(default: {DEFAULT_TYPE})')

    return parser.parse_args()


def create_dataset(output_file, samples_num, type_):
    with open(output_file, 'w', newline='') as csvfile:
        data_writer = csv.writer(csvfile, delimiter=' ',
                                 quotechar='|', quoting=csv.QUOTE_MINIMAL)

        if type_ == 'str':
            for _ in range(samples_num):
                data_writer.writerow([fake.name()])
        elif type_ == 'int':
            for _ in range(samples_num):
                data_writer.writerow([random.randint(-1000000, 1000000)])


if __name__ == '__main__':
    args = parse_args()

    # валидация аргументов
    if args.samples < 0:
        raise ValueError('Number of samples must be greater than 0.')

    if args.data_type not in AVAILABLE_TYPES:
        raise ValueError('This type is not available.')

    # запись данных в файл
    create_dataset(args.output, args.samples, args.data_type)
