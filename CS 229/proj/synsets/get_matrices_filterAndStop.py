import __builtin__
from gensim import *
import csv
import sys
import cPickle
from nltk.util import ngrams
from sets import Set
from nltk.corpus import stopwords


def get_reviews():
    filename = 'Data-1.0.csv'
    reader = csv.reader(open(filename, 'rb'), delimiter = ',')
    ids_reviews = {}
    ids_labels = {}
    i = 0
    for row in reader:
        if row[2] != 'Comment':
            ids_reviews[i] = row[2]
            ids_labels[i] = row[0]
            i += 1
    return [ids_reviews, ids_labels]

def preprocess(reviews):
    #Performing simple_preprocess
    for i in range(len(reviews)):
        if i%10 == 0: print 'Preprocessing review', i
    return reviews

def remove_stop(reviews):
    new_reviews = {}
    stop_words = Set(stopwords.words('english'))

    for review in reviews:
        new_reviews[review] = []
        for word in reviews:
            if word not in stop_words:
                new_reviews[review].append(word)
    return new_reviews

def add_ngrams(reviews):
    for i in range(len(reviews)):
        grams = []
        #getting ngrams
        for n in range(1, 3+1):
            grams = grams + ngrams(processed, n)
        reviews[i] = reviews[i] + grams
    return reviews

#function that removes tokens that only occur once in entire lexicon
def filt(reviews):
    word_counts = {}
    for review in reviews:
        for word in reviews[review]:
            if word not in word_counts:
                word_counts[word] = 1
            else:
                word_counts[word] += 1

    filter_words = Set()
    for word in word_counts:
        if word_counts[word] == 1:
          filter_words.add(word)

    return filter_words

def get_word_counts(reviews, type, fold):
    word_counts = {}
    for review in reviews:
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

def get_all_words(reviews, filter_words):
    words = Set()
    for i in range(len(reviews)):
        if i%10 == 0: print 'Getting unique words from review', i
        review = reviews[i]
        for word in review:
            if word not in words and word not in filter_words:
                words.add(word)
    words = sorted(list(words))
    print len(words)
    return words

def make_matrix(all_words, reviews, type, fold):
    writer = csv.writer(open('matrix_'+type+'_'+str(fold)+'.dat', 'wb'), delimiter = ' ')
    for i in range(len(reviews)):
        print 'On fold', fold, 'and type', type, 'writing row', i, 'of', len(reviews)
        review = reviews[i]
        counts = get_counts(review)
        for word in counts:
          if word in all_words:
            index = all_words.index(word)
            writer.writerow([i+1, index+1, counts[word]])

    #adding in zero count for bottom right corner of matrix if not there already
    if all_words[len(all_words)-1] not in counts:
        writer.writerow([len(reviews), len(all_words), 0])

def write_labels(labels, type, fold):
    writer = csv.writer(open('labels_'+type+'_'+str(fold)+'.dat', 'wb'), delimiter = ' ')
    for i in range(len(labels)):
        writer.writerow([labels[i]])

def get_full(all_words, reviews, labels):
    reviews_list = []
    labels_list = []
    for id in reviews:
        reviews_list.append(reviews[id])
        labels_list.append(labels[id])
    make_matrix(all_words, reviews_list, 'full', 0)
    write_labels(labels_list, 'full', 0)

def get_k_folds(words, reviews, labels, k):
    for fold in range(k):
        print 'Working on fold '+str(fold) +'...'
        test_ids = range(fold*(len(reviews)/k), (fold+1)*(len(reviews)/k))
        train_ids = range(fold*(len(reviews)/k)) + range((fold+1)*len(reviews)/k, len(reviews))
        test_set = []
        training_set = []
        test_labels = []
        training_labels = []
        for id in range(len(reviews)):
            if id in test_ids:
                test_set.append(reviews[id])
                test_labels.append(labels[id])
            else:
                training_set.append(reviews[id])
                training_labels.append(labels[id])
        make_matrix(words, test_set, 'test', fold)
        make_matrix(words, training_set, 'train', fold)
        write_labels(test_labels, 'test', fold)
        write_labels(training_labels, 'train', fold)

k = 10
print 'Getting reviews...'
results = get_reviews()
print 'Preprocessing reviews...'
ids_reviews = preprocess(results[0])
ids_reviews = remove_stop(ids_reviews)
ids_reviews = add_ngrams(ids_reviews)

ids_labels = results[1]

filter_words = filt(ids_reviews)

print 'Getting all words...'
all_words = get_all_words(ids_reviews, filter_words)
print 'Getting full data matrix'
get_full(all_words, ids_reviews, ids_labels)
#print 'Folding'
#get_k_folds(all_words, ids_reviews, ids_labels, k)
