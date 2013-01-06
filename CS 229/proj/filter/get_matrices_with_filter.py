import __builtin__
from gensim import *
import csv
import sys
import cPickle
from nltk.util import ngrams
from sets import Set

def get_comments():
    filename = 'Data-1.0.csv'
    reader = csv.reader(open(filename, 'rb'), delimiter = ',')
    ids_comments = {}
    ids_labels = {}
    i = 0
    for row in reader:
        if row[2] != 'Comment':
            ids_comments[i] = row[2]
            ids_labels[i] = row[0]
            i += 1
    return [ids_comments, ids_labels]

def preprocess(comments):
    #Performing simple_preprocess
    for i in range(len(comments)):
        if i%10 == 0: print 'Preprocessing review', i
        processed = utils.simple_preprocess(comments[i])
        grams = []
        #getting ngrams
        for n in range(2, 5+1):
            grams = grams + ngrams(processed, n)
        comments[i] = processed + grams

    return comments

def filt(comments):
    word_counts = {}
    for review in comments:
        for word in comments[review]:
            if word not in word_counts:
                word_counts[word] = 1
            else:
                word_counts[word] += 1

    filter_words = Set()
    filter_words.add('the')
    filter_words.add('http')
    for word in word_counts:
        if word_counts[word] == 1:
          filter_words.add(word)
    return filter_words

def get_word_counts(comments, type, fold):
    word_counts = {}
    for review in comments:
        for word in review:
            if word not in word_counts:
                word_counts[word] = 1
            else:
                word_counts[word] += 1
    return word_counts

def get_counts(review):
    counts = {}
    for word in review:
        if word not in counts:
            counts[word] = 1
        else:
            counts[word] += 1
    return counts

def get_all_words(comments, filter_words):
    words = Set()
    for i in range(len(comments)):
        if i%10 == 0: print 'Getting unique words from review', i
        review = comments[i]
        for word in review:
            if word not in words and word not in filter_words:
                words.add(word)
    words = sorted(list(words))
    print len(words)
    return words

def make_matrix(all_words, comments, type, fold):
    writer = csv.writer(open('matrix_'+type+'_'+str(fold)+'_n=5.dat', 'wb'), delimiter = ' ')
    for i in range(len(comments)):
        print 'On fold', fold, 'and type', type, 'writing row', i, 'of', len(comments)
        review = comments[i]
        counts = get_counts(review)
        for word in counts:
          if word in all_words:
            index = all_words.index(word)
            writer.writerow([i+1, index+1, counts[word]])

    #adding in zero count for bottom right corner of matrix if not there already
    if all_words[len(all_words)-1] not in counts:
        writer.writerow([len(comments), len(all_words), 0])

def write_labels(labels, type, fold):
    writer = csv.writer(open('labels_'+type+'_'+str(fold)+'.dat', 'wb'), delimiter = ' ')
    for i in range(len(labels)):
        writer.writerow([labels[i]])

def get_full(all_words, comments, labels):
    comments_list = []
    labels_list = []
    for id in comments:
        comments_list.append(comments[id])
        labels_list.append(labels[id])
    make_matrix(all_words, comments_list, 'full', 0)
    write_labels(labels_list, 'full', 0)

def get_k_folds(words, comments, labels, k):
    for fold in range(k):
        print 'Working on fold '+str(fold) +'...'
        test_ids = range(fold*(len(comments)/k), (fold+1)*(len(comments)/k))
        train_ids = range(fold*(len(comments)/k)) + range((fold+1)*len(comments)/k, len(comments))
        test_set = []
        training_set = []
        test_labels = []
        training_labels = []
        for id in range(len(comments)):
            if id in test_ids:
                test_set.append(comments[id])
                test_labels.append(labels[id])
            else:
                training_set.append(comments[id])
                training_labels.append(labels[id])
        make_matrix(words, test_set, 'test', fold)
        make_matrix(words, training_set, 'train', fold)
        write_labels(test_labels, 'test', fold)
        write_labels(training_labels, 'train', fold)

k = 10
print 'Getting comments...'
results = get_comments()
print 'Preprocessing comments...'
ids_comments = preprocess(results[0])
ids_labels = results[1]

filter_words = filt(ids_comments)

print 'Getting all words...'
all_words = get_all_words(ids_comments, filter_words)
print 'Getting full data matrix'
get_full(all_words, ids_comments, ids_labels)
#print 'Folding'
#get_k_folds(all_words, ids_comments, ids_labels, k)
