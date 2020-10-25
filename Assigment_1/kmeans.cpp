#include "kmeans.hpp"

/**
 * @brief kmeans_initialice_centroids
 * Initialize K centroids picking a random K patterns from dts.
 * @warning avoid select the same pattern several times.
 */
static void
kmeans_initialize_centroids(const std::vector<Pattern>& dts,
                                 size_t K,
                                 std::vector<Pattern>& centroids)
{
    //centroids.resize(K, Pattern(dts[0].dim()));
	centroids.clear();
    //TODO : WARNING AVOID SELECT THE SAME PATTERN SEVERAL TIMES.
    bool flag;
    size_t aux;

    for (size_t i = 0; i < K; )
    {
    	aux = rand() % dts.size();
    	flag = false;

    	for (size_t j = 0; j < centroids.size(); j++)
    	{
    		if(distance(dts[aux], centroids[j]) == 0)
    		{
    			flag = true;
    		}
    	}

    	if(!flag)
    	{
    		centroids.push_back(dts[aux]);
    		i++;
    	}
    }
}

/** @brief assign patterns to the nearest centroid.
 * Each pattern in dts will have the nearest centroid's label.
 * @return the number of changes carried out.
 */
static size_t
kmeans_assign_patterns(std::vector<Pattern>& dts,
                           std::vector<Pattern>& centroids)
{
    size_t num_changes = 0;

    //TODO
    float minor;
    int a;	//Patrón más cercano.

    for (size_t i = 0; i < dts.size(); i++)
    {
    	a = 0;
    	minor = distance(dts[i], centroids[0]);

    	for (size_t j = 0; j < centroids.size(); j++)
    	{
    		if(minor > distance(dts[i], centroids[j]))
    		{
    			minor = distance(dts[i], centroids[j]);
    			a = j;
    		}
    	}

    	if(dts[i].class_label() != a)
    	{
    		dts[i].set_class_label(a);
    		num_changes++;
    	}
    }

    return num_changes;
}

/**
 * @brief Given a dts, compute the centrois of each class label.
 * @param dts is the dataset.
 * @param centroids are the centroids.
 */
static void
kmeans_compute_centroids(const std::vector<Pattern>& dts,
                              const size_t K,
                              std::vector<Pattern>& centroids)
{
    /* reset centroids to zero.*/
    /*
    const size_t dim = dts[0].dim();
    if (centroids.size() != K)
        centroids.resize(K, Pattern(dts[0].dim()));
    for(size_t k=0; k<centroids.size(); ++k)
        centroids[k] = Pattern(dim, static_cast<int>(k));
    */
    //TODO
    centroids.clear();
    int counter = 0;
    float result;

    for (size_t i = 0; i < K; i++)
    {
    	Pattern p(dts[0].dim(), -1);
    	counter = 0;

    	for (size_t j = 0; j < dts.size(); j++)
    	{
    		if(dts[j].class_label() == i)
    		{
    			p += dts[j];
    			counter++;
    		}
    	}

    	for (size_t t = 0; t < dts[0].dim(); t++)
    	{
    		result = p[t] / counter;
    		p.set_value(t, result);
    	}

    	centroids.push_back(p);
    }
}


size_t
kmeans(std::vector<Pattern>& dts,
            const size_t K,
            const size_t max_iters,
            std::vector<Pattern>& centroids)
{

    /*Reset labels to -1 (none class).*/
    for(size_t i = 0; i < dts.size(); ++i)
        dts[i].set_class_label(-1);

    /*Initialice picking at random K patterns.*/
    kmeans_initialize_centroids(dts, K, centroids);

    size_t iter = 0;
    size_t num_changes;
    do
    {
        num_changes = kmeans_assign_patterns(dts, centroids);
        /* assign patterns to the nearest centroid. */
        if (num_changes>0)
            kmeans_compute_centroids (dts, K, centroids);
    }
    while (++iter < max_iters && num_changes>0);
    return iter;
}
