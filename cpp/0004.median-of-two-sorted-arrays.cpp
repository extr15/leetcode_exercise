
// AC
double findMedianSortedArrays(const vector<int>& nums1, const vector<int>& nums2) {
  const int l1 = nums1.size();
  const int l2 = nums2.size();
  int k = (l1 + l2) / 2;
  if ((l1 + l2) % 2) {
    return findKth(nums1.cbegin(), nums1.cend(), nums2.cbegin(), nums2.cend(), k + 1);
  } else {
    int v1 = findKth(nums1.cbegin(), nums1.cend(), nums2.cbegin(), nums2.cend(), k);
    int v2 = findKth(nums1.cbegin(), nums1.cend(), nums2.cbegin(), nums2.cend(), k + 1);
    return (v1 + v2) / 2.0;
  }
}
int findKth(const vector<int>::const_iterator& b1, const vector<int>::const_iterator& e1,
            const vector<int>::const_iterator& b2, const vector<int>::const_iterator& e2, int k) {
  int l1 = e1 - b1;
  int l2 = e2 - b2;
  if (l1 > l2) {
    return findKth(b2, e2, b1, e1, k);
  }
  if (b1 == e1) {
    return *(b2 + k - 1);
  }
  if (k == 1) {
    int v = std::min(*b1, *b2);
    return v;
  }
  int i1 = std::min(k / 2, l1);
  int i2 = k - i1;
  if (*(b1 + i1 - 1) < *(b2 + i2 - 1)) {
    int v = findKth(b1 + i1, e1, b2, b2 + i2, k - i1);
    return v;
  } else if (*(b1 + i1 - 1) > *(b2 + i2 - 1)) {
    int v = findKth(b1, b1 + i1, b2 + i2, e2, k - i2);
    return v;
  } else {
    return *(b1 + i1 - 1);
  }
}

// AC

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
  int l1 = nums1.size();
  int l2 = nums2.size();
  if (l1 > l2) {
    std::swap(nums1, nums2);
    l1 = nums1.size();
    l2 = nums2.size();
  }
  int half_len = (l1 + l2 + 1) / 2;
  int min_i = 0, max_i = l1;
  while (min_i <= max_i) {
    int i = (min_i + max_i) / 2;
    int j = half_len - i;
    if (i < l1 && nums2[j - 1] > nums1[i]) {
      min_i = i + 1;
    } else if (i > 0 && nums1[i - 1] > nums2[j]) {
      max_i = i - 1;
    } else {
      int max_left;
      if (i == 0) {
        max_left = nums2[j - 1];
      } else if (j == 0) {
        max_left = nums1[i - 1];
      } else {
        max_left = max(nums1[i - 1], nums2[j - 1]);
      }
      if ((l1 + l2) % 2 == 1) {
        return max_left;
      }
      int min_right;
      if (i == l1) {
        min_right = nums2[j];
      } else if (j == l2) {
        min_right = nums1[i];
      } else {
        min_right = min(nums1[i], nums2[j]);
      }
      return (max_left + min_right) / 2.0;
    }
  }
}

// AC
double findMedianSortedArrays(vector<int>& a, vector<int>& b) {
  if (a.size() > b.size()) {
    swap(a, b);
  }
  const int m = a.size();
  const int n = b.size();
  int left = 0, right = m + 1;
  const int half_len = (1 + m + n) / 2;
  while (left <= right) {
    int mid = (left + right) / 2;
    int k = half_len - mid;
    if (mid > 0 && a[mid - 1] > b[k]) {
      right = mid - 1;
    } else if (mid < m && a[mid] < b[k - 1]) {
      left = mid + 1;
    } else {
      int max_left;
      if (mid == 0) {
        max_left = b[k - 1];
      } else if (k == 0) {
        max_left = a[mid - 1];
      } else {
        max_left = max(a[mid - 1], b[k - 1]);
      }
      if ((m + n) % 2 != 0) {
        return max_left;
      }
      int min_right;
      if (mid == m) {
        min_right = b[k];
      } else if (k == n) {
        min_right = a[mid];
      } else {
        min_right = min(a[mid], b[k]);
      }
      return (max_left + min_right) / 2.0;
    }
  }
}
